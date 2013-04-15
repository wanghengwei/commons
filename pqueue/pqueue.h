#pragma once

#include <vector>
#include <map>
#include <mutex>
#include <functional>

#include <sys/poll.h>

bool operator < (pollfd const &left, pollfd const &right);

bool operator == (pollfd const &left, pollfd const &right);

namespace whw
{

  typedef std::function<void (int, short, int)> handler_t;

  class pqueue
  {
    
    std::vector<pollfd> m_fds;
    
    std::map<pollfd, handler_t> m_handlers;

    int m_max_events;

    std::mutex m_event_handler_lock;

  public:
    pqueue(int max_events = 100);

    ~pqueue();

    void register_event(int fd, short filter, handler_t handler);

    void unregister(int fd, short filter);

    void dispatch();

    bool has_work() const;

  };

}
