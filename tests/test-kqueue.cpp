#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <kqueue/kqueue.h>

TEST_CASE("kqueue/empty-test", "empty test")
{

}

TEST_CASE("kqueue/empty-work-test", "empty work queue")
{
  whw::kqueue q;
  while (q.has_work()) {
    q.dispatch();
  }
}
