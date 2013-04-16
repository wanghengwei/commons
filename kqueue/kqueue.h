#pragma once

//std
#include <functional>
#include <map>
#include <mutex>

//sys
#include <sys/event.h>
#include <sys/types.h>

//for hold in std::map
bool operator < (struct ::kevent const &left, struct ::kevent const &right);

namespace whw
{

  class kqueue
  {
    
  public:
    
    typedef std::function<void (int /* fd */, int /* data_size  */, int /* error  */)> handler_t;
    
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

    void unregister_event(int fd, int filter);

    void unregister_fd(int fd);
   
    int dispatch(long sec = 0, long ns = 0);

    template<typename Rep, typename Period>
    int dispatch(std::chrono::duration<Rep, Period> time_out)
    {

      long t1 = std::chrono::duration_cast<std::chrono::seconds>(time_out).count();
      long t2 = (std::chrono::duration_cast<std::chrono::nanoseconds>(time_out) - 
		 std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(t1))).count();
      return dispatch(t1, t2);

    }

    int file_handle() const;
    
  };
  
}
