#pragma once

#include <functional>
#include <map>
#include <mutex>

#include <sys/event.h>
#include <sys/types.h>

bool operator < (struct ::kevent const &left, struct ::kevent const &right);

namespace whw
{

  class kqueue
  {
    
  public:
    
    typedef std::function<void (int, int, int)> handler_t;
    
  private:
    
    int m_kq;

    struct ::kevent *m_event_list;
    
    int m_max_events;
    
    std::map<struct ::kevent, handler_t> m_handlers;

    std::mutex m_event_handler_lock;
    
  public:

    kqueue(int max_events = 100);

    ~kqueue();

    void register_event(int fd, int filter, handler_t handler, bool is_oneshot = false, bool is_et = true);
   
    void dispatch();

    int file_handle() const;
    
  };
  
}
