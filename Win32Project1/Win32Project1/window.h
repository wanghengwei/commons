#pragma once
#include <string>

class RenderAdaptor;

//represent a windows' window.
class Window
{

	HINSTANCE m_app;

	HWND m_hwnd;

public:

	Window(HINSTANCE app_inst, std::wstring const &wnd_class_name, std::wstring const &title);

	~Window()
	{

	}

	operator bool () const;

	HWND handle() const;

	void show(int show_style = SW_NORMAL);

	int GetHeight() const
	{
		RECT r;
		GetWindowRect(m_hwnd, &r);
		return r.top - r.bottom;
	}

	int GetWidth() const
	{
		RECT r;
		GetWindowRect(m_hwnd, &r);
		return r.right - r.left;
	}
	
#pragma region 派生类选择继承以下方法

	//called when WM_PAINT message occurred
	virtual void on_paint(RenderAdaptor * renderer)
	{

	}

	//called when WM_MOUSEMOVE msg occurred
	virtual void on_mouse_move(int x, int y)
	{

	}

	virtual void on_mouse_left_down(int x, int y)
	{

	}

#pragma endregion

private:
	
	int process_message(UINT msg, WPARAM wp, LPARAM lp);

	static LRESULT CALLBACK wnd_proc_delegate(HWND, UINT, WPARAM, LPARAM);
};

