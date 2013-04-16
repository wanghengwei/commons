#include <kqueue/kqueue.h>

#include <string>

#include <string.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

using whw::kqueue;

bool operator < (struct kevent const &left, struct kevent const &right)
{

  return left.ident < right.ident || (left.ident == right.ident && left.filter < right.filter);

}

kqueue::kqueue(int max_events) : m_max_events(max_events)
{

  m_event_list = new struct kevent[m_max_events];
  m_kq = ::kqueue();

}

kqueue::~kqueue()
{

  close(m_kq);
  delete[] m_event_list;

}

void kqueue::register_event(int fd, int filter, handler_t handler, bool is_oneshot, bool is_et)
{

  struct kevent ev;

  int flag = EV_ADD;
  if (is_oneshot)
    flag |= EV_ONESHOT;
  if (is_et)
    flag |= EV_CLEAR;

  EV_SET(&ev, fd, filter, flag, 0, 0, 0);

  {
    lock_guard<mutex> lg(m_event_handler_lock);

    if (-1 == kevent(m_kq, &ev, 1, nullptr, 0, nullptr)) {
      throw string(strerror(errno));
    }

    m_handlers[ev] = handler;

  }
}

void kqueue::unregister_event(int fd, int filter)
{
  struct kevent ev;
  EV_SET(&ev, fd, filter, EV_DELETE, 0, 0, nullptr);

  {
    lock_guard<mutex> lg(m_event_handler_lock);
    if (-1 == kevent(m_kq, &ev, 1, nullptr, 0, nullptr)) {
      int e = errno;
      if (e != 2) {
	throw string(strerror(e));
      }
    }
    m_handlers.erase(ev);
  }
}

void kqueue::unregister_fd(int fd)
{
  for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it) {
    if (it->first.ident != fd) {
      continue;
    }

    {
      lock_guard<mutex> lg(m_event_handler_lock);

      struct kevent ev = it->first;
      EV_SET(&ev, fd, ev.filter, EV_DELETE, 0, 0, nullptr);
      if (-1 == kevent(m_kq, &ev, 1, nullptr, 0, nullptr)) {
	int e = errno;
	if (e != 2)
	  throw string(strerror(errno));
      }
      it = m_handlers.erase(it);
      if (it == m_handlers.end()) {
	break;
      }
    }
  }
}

int kqueue::dispatch(long t1, long t2)
{

  timespec t = { t1, t2 };
  timespec *pt = nullptr;
  if (t1 != 0 || t2 != 0)
    pt = &t;

  //The core function!
  int n = ::kevent(m_kq, nullptr, 0, m_event_list, m_max_events, pt);

  if (-1 == n) {
    throw string(strerror(errno));
  }

  for (int i = 0; i < n; i++) {

    auto const &ev = m_event_list[i];


    int err_code = 0;
    if (ev.flags & EV_ERROR)
      err_code = ev.data;

    //The remote connection closed
    //TODO is it good to do so?
    if (ev.flags & EV_EOF) {
      if (!err_code) {
	//Manually set the error to BAD file descriptor
	err_code = EBADF;
      }
    }

    int data_size = err_code ? 0 : ev.data;

    handler_t handler;
    {
      lock_guard<mutex> lg(m_event_handler_lock);
      
      auto it = m_handlers.find(ev);
      
      if (it == m_handlers.end()) {
	//An event which doesn't exist in registry occurred.
	continue;
      }
      
      handler = it->second;

      //If the event is set to EV_ONESHOT, the it has been removed
      //from the kqueue. We should remove the handler manually.
      if (ev.flags & EV_ONESHOT)
	m_handlers.erase(ev);

    }

    handler(ev.ident, data_size, err_code);

  }
  return n;
}

int kqueue::file_handle() const
{
  return m_kq;
}

void read_handler(int fd, int sz, int err)
{
  if (err) {
    //log error
    printf("Event READ error: %s\n", strerror(err));
  }
  else {
    char *buf = new char[sz];
    auto x = read(fd, buf, sz);
    if (x != sz) {
      printf("There should be %d bytes to read, but only get %ld bytes\n", sz, x);
    }
    else {
    printf("Received message: %s\n", buf);

    if (buf[1] == 'i')
      buf[1] = 'o';
    else
      buf[1] = 'i';

    write(fd, buf, sz);
    }
    delete[] buf;

    close(fd);
  }
}

/*
int main(int, char const *[])
{
  whw::kqueue q(100);
  int s[2];
  socketpair(PF_LOCAL, SOCK_STREAM, 0, s);
  int reader = s[0];
  int writer = s[1];
  int nb = 1;
  ioctl(writer, FIONBIO, &nb);  
  ioctl(reader, FIONBIO, &nb);

  int connector = socket(PF_INET, SOCK_STREAM, 0);
  ioctl(connector, FIONBIO, &nb);

  q.register_event(connector, EVFILT_WRITE, [](int fd, int sz, int err) {
      if (err) {
	printf("error in event: code %d\n", err);
	return;
      }
      printf("Event WRITE triggerred, buffer size is %d\n", sz);
      sockaddr_in addr;
      socklen_t addr_len = sizeof(addr);
      if (-1 == getpeername(fd, (sockaddr *)&addr, &addr_len)) {
	//printf("ERRPOR : %s\n", strerror(errno));       
      }
    }, true);
  /*
  q.register_event(writer, EVFILT_WRITE, [&q](int fd, int sz, int err) {
      if (err)
	return;
      q.unregister_event(fd, EVFILT_WRITE);
      q.register_event(fd, EVFILT_READ, &read_handler);
      char const msg[] = "ping!";
      write(fd, msg, sizeof(msg));


    });

  q.register_event(reader, EVFILT_READ, &read_handler);
  
  ///

  sockaddr_in addr;
  addr.sin_family = PF_INET;
  addr.sin_port = htons(30416);
  addr.sin_addr.s_addr = inet_addr("192.168.3.238");
  connect(connector, (sockaddr *)&addr, sizeof(addr));

  while (true) {
    q.dispatch(milliseconds(100));
  }
}
*/
