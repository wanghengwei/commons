#include <coroutine.h>
#include <thread>

using namespace std;
USING_H3D_NS

coroutine::coroutine(function<void (coroutine *)> f) : func(f)
{
	if (!func)
		return;

	unique_lock<mutex> lk(mtx);
	new thread(bind(func, this));
	cv.wait(lk);
}

void coroutine::yield()
{
	unique_lock<mutex> lk(mtx);
	cv.notify_one();
	cv.wait(lk);
}

void coroutine::operator () ()
{
	unique_lock<mutex> lk(mtx);
	cv.notify_one();
	cv.wait(lk);
}
