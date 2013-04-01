#pragma once
#include <string>
#include <chrono>

namespace whw
{
    class duration_counter
    {
	std::chrono::high_resolution_clock::time_point start_time;
	std::string work_name;

    public:
	duration_counter(std::string const & work_name = "");

	~duration_counter();
    };
}
