#include "pqueue.h"
#include <string.h>

using namespace std;

bool operator < (pollfd const &left, pollfd const &right)
{
  
  return left.fd < right.fd || (left.fd == right.fd && left.events < right.events);
  
}

whw::pqueue::pqueue(int max_events) : m_max_events(max_events)
{
  
  m_fds.reserve(max_events);
  
}

void whw::pqueue::register_event(int fd, short filter, whw::handler_t handler)
{
  
  pollfd pfd = {fd, filter};
  
  lock_guard<mutex> lg(m_event_handler_lock);
  
  if (m_handlers.find(pfd) != m_handlers.end())
    throw string("Can't register the existing event");
  
  if (m_fds.size() == m_max_events)
    throw string("Can't register new events");
  
  m_fds.push_back(pfd);
  m_handlers.insert({pfd, handler});
  
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

    m_handlers[m_fds[i]](m_fds[i].fd);

    n--;

  }

}
