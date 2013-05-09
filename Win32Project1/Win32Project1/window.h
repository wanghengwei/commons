#pragma once
#include <string>

//represent a windows' window.
class window
{

	HINSTANCE m_app;

	HWND m_hwnd;

public:
	window(HINSTANCE app_inst, std::wstring const &wnd_class_name, std::wstring const &title);

	~window()
	{

	}

	//return false if the handle of window is invalid
	operator bool () const;

	HWND handle() const;

	//
	void show(int show_style = SW_NORMAL);
	
#pragma region The methods which derived classes must override

	//called when WM_PAINT message occurred
	virtual void on_paint()
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

