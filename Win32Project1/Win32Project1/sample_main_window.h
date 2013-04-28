#pragma once
#include "base_window.h"

class sample_main_window : public base_window
{
public:

	sample_main_window(HINSTANCE app_inst, std::wstring const &class_name);

	void render(HDC, PAINTSTRUCT const&) override;
};

