#include <profiler/duration_counter.h>
#include <iostream>
#include <sstream>

using namespace std;
using namespace std::chrono;

whw::duration_counter::duration_counter(string const & work_name) : start_time(high_resolution_clock::now()), work_name(work_name)
{
}

whw::duration_counter::~duration_counter()
{
    stringstream ss;
    ss << "[" << work_name << "]: " << duration_cast<milliseconds>(high_resolution_clock::now() - start_time).count() << " millisecond(s).\n";
    cout << ss.str();
}
