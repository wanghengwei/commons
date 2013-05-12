#include "stdafx.h"
#include "Win32Project1.h"
#include "MainWindow.h"
#include "RectButton.h"
#include "Scrollbar.h"
#include <chrono>
#include <thread>

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

struct AEvent : BaseEvent {};

struct AState : TBaseState<AState>
{

	void OnEnter() { OutputDebugString(L"Enter AState!"); }

	typedef TVector<
		Transition<AEvent, AState, &AState::OnEnter>
	> Reactions;

	AState()
	{
		OutputDebugString(L"AState()");
	}

	~AState()
	{
		OutputDebugString(L"~AState()");
	}
};

int WINAPI wWinMain(HINSTANCE app_instance, HINSTANCE, LPWSTR cmd_line, int show_style)
{
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