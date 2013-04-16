#include "kqueue.h"

#include <string>

#include <string.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>

using std::string;
using std::mutex;
using std::lock_guard;
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
      //TODO log error
      return;
    }

    m_handlers[ev] = handler;

  }
}

void kqueue::dispatch()
{

  int n = ::kevent(m_kq, nullptr, 0, m_event_list, m_max_events, nullptr);

  if (-1 == n) {
    throw string(strerror(errno));
  }

  for (int i = 0; i < n; i++) {

    auto const &ev = m_event_list[i];

    handler_t handler;

    {
      lock_guard<mutex> lg(m_event_handler_lock);
      
      auto it = m_handlers.find(ev);
      
      if (it == m_handlers.end()) {
	//An event which doesn't exist in registry occurred.
	continue;
      }
      
      handler = it->second;

      if (ev.flags & EV_ONESHOT)
	m_handlers.erase(ev);

    }

    handler(ev.ident, ev.data, ev.flags & EV_ERROR ? ev.data : 0);

  }

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
  }
}

int main(int, char const *[])
{
  whw::kqueue q(100);
  int s[2];
  socketpair(PF_LOCAL, SOCK_STREAM, 0, s);
  int reader = s[0];
  int writer = s[1];
  int nb = 1;
  ioctl(writer, FIONBIO, &nb);

  q.register_event(writer, EVFILT_WRITE, [&q](int fd, int sz, int err) {
      if (err)
	return;
      q.register_event(fd, EVFILT_READ, &read_handler);
      char const msg[] = "ping!";
      write(fd, msg, sizeof(msg));


    }, true);

  q.register_event(reader, EVFILT_READ, &read_handler);

  while (true) {
  q.dispatch();
  }
}
