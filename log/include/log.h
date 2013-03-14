#pragma once
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>

template<typename OS>
class logger
{
	template<typename... Args>
		static void concat(std::stringstream &ss);

	static void concat(std::stringstream &ss)
	{
		ss << "\n";
	}

	template<typename H, typename ... T>
		static void concat(std::stringstream &ss, H head, T ... tail)
		{
			ss << head;
			concat(ss, tail ...);
		}

public:
	template<typename ... Args>
		static void debug(Args ... args)
		{
			std::stringstream ss;
			ss << "[t " << std::this_thread::get_id() << "] ";
			concat(ss, args ...);
			*_os << ss.str();
		}
private:
	static OS * _os;
};

typedef logger<std::ostream> clogger;
