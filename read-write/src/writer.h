#pragma once
#include "actor.h"
#include <iostream>
#include <mutex>
#include <condition_variable>
class Writer : public Actor
{
	public:
		void work() override
		{
			wait();

			std::cout << "writer working..." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));

			signal();
		}

		static void wait()
		{
			std::clog << std::this_thread::get_id() << ": lock writer..." << std::endl;
			_lock.lock();
			std::clog << std::this_thread::get_id() << ": own writer locker" << std::endl;
		}

		static void signal()
		{
			std::clog << std::this_thread::get_id() << ": unlock writer..." << std::endl;
			_lock.unlock();
			std::clog << std::this_thread::get_id()  << ": unlock writer done" << std::endl;
		}
	private:
		static std::mutex _mtx;
		static std::unique_lock<std::mutex> _lock;
};

std::mutex Writer::_mtx;
std::unique_lock<std::mutex> Writer::_lock(_mtx, std::defer_lock);
