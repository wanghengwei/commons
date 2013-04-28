#include "stdafx.h"
#include "base_window.h"
#include <algorithm>

using namespace std;

base_window::base_window(HINSTANCE app_inst, std::wstring const & class_name) : m_app(app_inst), m_class_name(class_name)
{

	WNDCLASS wc = {};
	wc.hInstance = m_app;
	wc.lpszClassName = m_class_name.c_str();
	wc.lpfnWndProc = &wnd_proc_delegate;

	RegisterClass(&wc);

	m_hwnd = CreateWindowEx(0, m_class_name.c_str(), L"this is a sample of window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, app_inst, nullptr);

	SetWindowLongPtr(m_hwnd, GWLP_USERDATA, LONG(this));
}

base_window::operator bool () const
{
	return 0 != m_hwnd;
}

HWND base_window::handle() const
{
	return m_hwnd;
}

void base_window::show(int show_style)
{
	ShowWindow(m_hwnd, show_style);
}

LRESULT base_window::wnd_proc_delegate(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	auto p = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	if (!p) {
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	else {
		base_window *self = reinterpret_cast<base_window *>(p);
		return self->process_message(msg, wp, lp);
	}
}

LRESULT base_window::process_message(UINT msg, WPARAM wp, LPARAM lp)
{
	switch(msg) 
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps = {};
			HDC hdc = BeginPaint(handle(), &ps);
			render(hdc, ps);
			EndPaint(handle(), &ps);
		}
		break;
	case WM_MOUSEMOVE:
		cursor().set_pos(lp);
		break;
	case WM_NCLBUTTONDOWN:
		find_out_active(GET_X_LPARAM(lp), GET_Y_LPARAM(lp));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(handle(), msg, wp, lp);
}
