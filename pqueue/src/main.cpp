#include <vector>
#include <map>
#include <functional>
#include <string>
#include <mutex>
#include <sys/socket.h>
#include <sys/poll.h>
#include <string.h>

using namespace std;



int main(int, char const *[])
{

  int socks[2];
  assert(0 == socketpair(PF_LOCAL, SOCK_STREAM, 0, socks));
  int reader = socks[0];
  int writer = socks[1];

  int nb = 1;
  ioctl(reader, FIONBIO, &nb);
  ioctl(writer, FIONBIO, &nb);

  event_queue eq;
  eq.register_event(reader, POLLIN, [](int fd) 
		    {
		      
		      char buf[1024];
		      int r = read(fd, buf, sizeof(buf));
		      cout << string(buf, buf + r) << endl;
		      
		    });
  
  char const msg[] = "hello";
  write(writer, msg, sizeof(msg));

  eq.dispatch();

  return 0;
}
