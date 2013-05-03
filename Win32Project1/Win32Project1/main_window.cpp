#include "stdafx.h"
#include "main_window.h"

using namespace std;

main_window::main_window(HINSTANCE app_inst) : window(app_inst, L"main_window", L"sample_main_window"), widget("")
{

}


void main_window::render(HDC hdc, PAINTSTRUCT const &ps)
{

	react_state();

	FillRect(hdc, &ps.rcPaint, pre_defined_background[background_index]);

	widget::render(hdc, ps);

}