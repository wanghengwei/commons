#pragma once
#include "actor.h"
#include "writer.h"
//#if defined(_GLIBCXX_HAVE_TLS)
//#undef _GLIBCXX_HAVE_TLS
//#endif
#include <mutex>
#include <thread>
#include <iostream>

class Reader : public Actor
{
	public:
		void work() override
		{
			_mtx.lock();
			_cnt++;
			if (_cnt == 1)
			{
				//std::cout << "first reader, try to wait writer..." << std::endl;
				Writer::wait();
			}
			_mtx.unlock();

			std::cout << "reader working... there're " << _cnt << " reader left" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

			_mtx.lock();
			_cnt--;
			if (_cnt == 0)
			{
				//std::cout << "no reader left, signal writer..." << std::endl;
				Writer::signal();
			}
			_mtx.unlock();
		}

	private:
		static unsigned int _cnt;
		static std::mutex _mtx;
};

unsigned int Reader::_cnt = 0;
std::mutex Reader::_mtx;
