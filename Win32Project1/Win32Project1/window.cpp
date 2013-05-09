#include "stdafx.h"
#include "window.h"
#include "RenderAdaptor.h"

using namespace std;

Window::Window(HINSTANCE app_inst, wstring const &wnd_class_name, std::wstring const &title) : m_app(app_inst)
{

	WNDCLASS wc = {};
	wc.hInstance = m_app;
	wc.lpszClassName = wnd_class_name.c_str();
	wc.lpfnWndProc = &wnd_proc_delegate;

	RegisterClass(&wc);

	m_hwnd = CreateWindowEx(0, wnd_class_name.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, app_inst, nullptr);

	SetWindowLongPtr(m_hwnd, GWLP_USERDATA, LONG(this));
}

Window::operator bool () const
{
	return 0 != m_hwnd;
}

HWND Window::handle() const
{
	return m_hwnd;
}

void Window::show(int show_style)
{
	ShowWindow(m_hwnd, show_style);
}

LRESULT Window::wnd_proc_delegate(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	auto p = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	if (!p) {
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	else {
		Window *self = reinterpret_cast<Window *>(p);
		return self->process_message(msg, wp, lp);
	}
}

int Window::process_message(UINT msg, WPARAM wp, LPARAM lp)
{
	switch(msg) 
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(handle(), &ps);
			static RenderAdaptor *r = new RenderAdaptor(hdc);
			on_paint(r);
			EndPaint(handle(), &ps);
		}
		break;
	case WM_MOUSEMOVE:
		on_mouse_move(GET_X_LPARAM(lp), GET_Y_LPARAM(lp));
		break;
	case WM_LBUTTONDOWN:
		on_mouse_left_down(GET_X_LPARAM(lp), GET_Y_LPARAM(lp));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(handle(), msg, wp, lp);
}
