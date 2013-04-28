#include "stdafx.h"
#include "Win32Project1.h"
#include "sample_main_window.h"
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
			RedrawWindow(hwnd, nullptr, 0, RDW_INVALIDATE);
		}
	});
}

int WINAPI wWinMain(HINSTANCE app_instance, HINSTANCE, LPWSTR cmd_line, int show_style)
{

	sample_main_window main_win(app_instance, L"SampleWindow");

	if (!main_win)
		return -1;

	main_win.show(show_style);

	run_frame_announcement(main_win.handle());
	run_main_loop();

	return 0;
}