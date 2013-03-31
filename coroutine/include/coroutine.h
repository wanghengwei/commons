#pragma once

#include <global.h>

#include <mutex>
#include <condition_variable>
#include <functional>

BEGIN_H3D_NS

class coroutine
{
	std::function<void (coroutine *)> func;
	std::condition_variable cv;
	std::mutex mtx;

public:
	//run f as a coroutine immediately
	coroutine(std::function<void (coroutine *)> f);

	//yield the coroutine. Must be called in coroutine.
	void yield();

	//Continue a coroutine. Must be called in main thread.
	void operator () ();
};

END_H3D_NS
