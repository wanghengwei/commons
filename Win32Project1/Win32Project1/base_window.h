#pragma once
#include "window.h"
#include "cursor.h"
#include <string>
#include <map>
#include <cstdint>

class base_window : public window
{

	HINSTANCE m_app;

	std::wstring m_class_name;

	HWND m_hwnd;

	cursor_t m_cursor;

public:
	base_window(HINSTANCE app_inst, std::wstring const & class_name);

	~base_window() {}

	operator bool () const;

	HWND handle() const;

	void show(int show_style);

	void hide()
	{
		show(SW_HIDE);
	}

	cursor_t& cursor() override { return m_cursor; }

	cursor_t const & cursor() const override { return m_cursor; }

	virtual LRESULT process_message(UINT msg, WPARAM wp, LPARAM lp);

private:

	static LRESULT CALLBACK wnd_proc_delegate(HWND, UINT, WPARAM, LPARAM);
};

