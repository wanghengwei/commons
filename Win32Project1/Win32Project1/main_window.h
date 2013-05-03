#pragma once
#include "window.h"
#include "widget.h"
#include "mouse_pointer.h"
#include "state.h"

class main_window : public window, public widget, protected state
{

	//HBRUSH m_background;
	 
	//widget *m_hot_widget;

	mouse_pointer m_pointer;

public:

	main_window(HINSTANCE app_inst);

	~main_window()
	{
		//DeleteObject(m_background);
	}

	mouse_pointer & pointer() override
	{
		return m_pointer;
	}

	mouse_pointer const & pointer() const override
	{
		return m_pointer;
	}

	//widget * hot_widget() override
	//{
	//	return m_hot_widget;
	//}

	state & global_state()
	{
		return *this;
	}

	//override window::on_paint
	void on_paint() override
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(handle(), &ps);
		render(hdc, ps);
		EndPaint(handle(), &ps);
	}

	void on_mouse_move(int x, int y) override
	{
		pointer().position(x, y);
		hot_widget = find_widget_at(pointer().position());
	}

	void on_mouse_lbutton_down(int x, int y) override
	{
		pointer().position(x, y);
		active_widget = find_widget_at(point_t(x, y));
	}

	void render(HDC, PAINTSTRUCT const&) override;

};

