#include "stdafx.h"
#include "Win32Project1.h"
#include "MainWindow.h"
#include "RectButton.h"
#include "Scrollbar.h"
#include <chrono>
#include <thread>
#define BOOST_STATECHART_USE_NATIVE_RTTI
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/mpl/list.hpp>

namespace sc = boost::statechart;
namespace mpl = boost::mpl;

using namespace std;
using namespace std::chrono;

void run_main_loop()
{
	MSG msg = {};
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void run_frame_announcement(HWND hwnd)
{
	new thread([hwnd]() {
		auto tp = steady_clock::now();
		auto const interval = milliseconds(1000/30);

		while (true) {
			tp += interval;
			this_thread::sleep_until(tp);
			RedrawWindow(hwnd, nullptr, 0, RDW_INVALIDATE | RDW_ERASENOW | RDW_ALLCHILDREN);
		}
	});
}

struct AEvent : sc::event<AEvent> {};

struct BEvent : sc::event<BEvent> {};

struct Greeting;

struct MyMachine : sc::state_machine<MyMachine, Greeting> {};

struct Goodbye : sc::simple_state<Goodbye, MyMachine> 
{
	Goodbye()
	{
		OutputDebugString(L"Goodbye()");
	}
	~Goodbye()
	{
		OutputDebugString(L"~Goodbye()");
	}
};

struct Greeting : sc::simple_state<Greeting, MyMachine>
{
	Greeting()
	{
		OutputDebugString(L"Greeting()");
	}
	~Greeting()
	{
		OutputDebugString(L"~Greeting()");
	}

	typedef mpl::list<
		sc::transition<AEvent, Goodbye>,
		sc::transition<BEvent, Greeting>
	> reactions;
};

int WINAPI wWinMain(HINSTANCE app_instance, HINSTANCE, LPWSTR cmd_line, int show_style)
{

	MyMachine mm;
	mm.initiate();
	mm.process_event(BEvent());
	mm.process_event(AEvent());

	MainWindow main_win(app_instance);

	if (!main_win)
		return -1;

	//RectButton *btn = new RectButton("btn1", &main_win);
	//btn->Position(300, 300);
	//main_win.add(btn);

	Scrollbar bar("sb1", &main_win);
	main_win.add(&bar);

	main_win.show(show_style);

	run_frame_announcement(main_win.handle());
	run_main_loop();

	return 0;
}