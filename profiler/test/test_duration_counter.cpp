#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <profiler/duration_counter.h>
#include <thread>
#include <chrono>

using namespace std;

TEST_CASE("profiler/duration_counter", "duration counter test")
{
    {
	whw::duration_counter counter;
    }

    {
	whw::duration_counter counter("work1");
	this_thread::sleep_for(chrono::seconds(1));
    }
}

