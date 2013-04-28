#include "stdafx.h"
#include "sample_main_window.h"
#include "rect_button.h"

using namespace std;

sample_main_window::sample_main_window(HINSTANCE app_inst, wstring const &class_name) : base_window(app_inst, class_name)
{
	rect_button *btn = new rect_button(this);
	btn->position(100, 100);
}


void sample_main_window::render(HDC hdc, PAINTSTRUCT const &ps)
{
	FillRect(hdc, &ps.rcPaint, HBRUSH(COLOR_WINDOW + 1));

	window::render(hdc, ps);
}