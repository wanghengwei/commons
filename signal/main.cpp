#include <iostream>
#include <chrono>
#include <functional>
#include <boost/signals2.hpp>

using namespace std;
using namespace std::chrono;
namespace signals = boost::signals2;

int f(int x)
{
    return ++x;
}

class duration_counter
{
    high_resolution_clock::time_point start_time;
    string work_name;

    public:
	duration_counter(string const & work_name = "") : start_time(high_resolution_clock::now()), work_name(work_name)
	{
	}

	~duration_counter()
	{
	    cout << "[" << work_name << "] duration is " << duration_cast<milliseconds>(high_resolution_clock::now() - start_time).count() << " millisecond(s)." << endl;
	}
};

int main(int, char const * [])
{
    signals::signal<int (int)>  sig;

    sig.connect(bind(f, placeholders::_1));

    unsigned N = 10000000;
    {
	duration_counter counter("signal call");
	for (unsigned i = 1; i <= N; i ++)
	    sig(i);
    }

    {
	duration_counter counter("directly call");
	int r = 0;
	for (unsigned i = 1; i <= N; i ++)
	{
	    r = f(r);
	}
	cout << r << endl;
    }

    {
	duration_counter counter("lambda call");
	int r = 0;
	for (unsigned i = 1; i <= N; i ++)
	{
	    r = [](int x) { return f(x); } (r);
	}
	cout << r << endl;
    }
}
