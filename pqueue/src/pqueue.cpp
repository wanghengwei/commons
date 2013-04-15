#include <pqueue/pqueue.h>
#include <string.h>
#include <algorithm>

using namespace std;

bool operator < (pollfd const &left, pollfd const &right)
{
  
  return left.fd < right.fd || (left.fd == right.fd && left.events < right.events);
  
}

bool operator == (pollfd const &left, pollfd const &right)
{
  return left.fd == right.fd && left.events == right.events;
}

whw::pqueue::pqueue(int max_events) : m_max_events(max_events)
{
  
  m_fds.reserve(max_events);
  
}

whw::pqueue::~pqueue()
{
  
}

void whw::pqueue::register_event(int fd, short filter, whw::handler_t handler)
{
  
  printf("0000\n");
  pollfd pfd = {fd, filter, 0};
  printf("1111\n");
  lock_guard<mutex> lg(m_event_handler_lock);
  printf("xxx\n");
  if (m_handlers.find(pfd) != m_handlers.end())
    throw string("Can't register the existing event");
  printf("__aa\n");
  if (m_fds.size() == m_max_events)
    throw string("Can't register new events");
  printf("aaa\n");
  m_fds.push_back(pfd);
  printf("bb\n");
  m_handlers.insert({pfd, handler});
  printf("cc\n");
}

void whw::pqueue::unregister(int fd, short filter)
{

  lock_guard<mutex> lg(m_event_handler_lock);

  pollfd t = {fd, filter, 0};

  m_fds.erase(remove(m_fds.begin(), m_fds.end(), t), m_fds.end());

  m_handlers.erase(t);

}

void whw::pqueue::dispatch()
{

  int n = poll(m_fds.data(), m_fds.size(), -1);
  if (-1 == n) {
    throw string(strerror(errno));
  }

  for (int i = 0; i < m_max_events && n > 0; i++) {

    if (!m_fds[i].revents)
      continue;

    m_handlers[m_fds[i]](m_fds[i].fd, m_fds[i].revents, m_fds[i].revents & POLLERR ? errno : 0);

    n--;

  }

}

bool whw::pqueue::has_work() const
{
  return !m_fds.empty();
}
