#pragma once
#include "RenderAdaptor.h"
#include "Events.h"
#include <string>

template<typename Derived>
class Window
{

	HINSTANCE m_app;

	HWND m_hwnd;

public:

	Window(HINSTANCE app_inst, std::wstring const &wnd_class_name, std::wstring const &title) : m_app(app_inst)
	{

		WNDCLASS wc = {};
		wc.hInstance = m_app;
		wc.lpszClassName = wnd_class_name.c_str();
		wc.lpfnWndProc = &wnd_proc_delegate;

		RegisterClass(&wc);

		m_hwnd = CreateWindowEx(0, wnd_class_name.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, app_inst, nullptr);

		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, LONG(this));
	}

	~Window()
	{

	}

	operator bool () const
	{
		return 0 != m_hwnd;
	}

	HWND handle() const
	{
		return m_hwnd;
	}

	void show(int show_style = SW_NORMAL)
	{
		ShowWindow(m_hwnd, show_style);
	}

	int GetClientHeight() const
	{
		RECT r;
		GetClientRect(m_hwnd, &r);
		return r.top - r.bottom;
	}

	int GetClientWidth() const
	{
		RECT r;
		GetClientRect(m_hwnd, &r);
		return r.right - r.left;
	}

#pragma region 派生类选择继承以下方法

	//called when WM_PAINT message occurred
	//virtual void on_paint(RenderAdaptor * renderer)
	//{

	//}

	//called when WM_MOUSEMOVE msg occurred
	//virtual void on_mouse_move(int x, int y)
	//{

	//}

	//virtual void on_mouse_left_down(int x, int y)
	//{

	//}

#pragma endregion

private:

	int process_message(UINT msg, WPARAM wp, LPARAM lp)
	{
		switch(msg) 
		{
		case WM_PAINT:
			{
				
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(handle(), &ps);

				static RenderAdaptor *r = new RenderAdaptor(hdc);

				PaintEvent ev(r);

				Output out = static_cast<Derived *>(this)->Transit(ev);
				out();

				EndPaint(handle(), &ps);

			}
			break;
		case WM_SIZE:
			{
				ReSizedEvent ev = {HIWORD(lp), LOWORD(lp)};
				Output out = static_cast<Derived *>(this)->Transit(ev);
				out();
			}
			break;
		case WM_MOUSEMOVE:
			//on_mouse_move(GET_X_LPARAM(lp), GET_Y_LPARAM(lp));
			break;
		case WM_LBUTTONDOWN:
			//on_mouse_left_down(GET_X_LPARAM(lp), GET_Y_LPARAM(lp));
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}

		return DefWindowProc(handle(), msg, wp, lp);
	}


	static LRESULT CALLBACK wnd_proc_delegate(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
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
};

