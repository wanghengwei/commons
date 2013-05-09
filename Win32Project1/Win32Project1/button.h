#pragma once
#include "Widget.h"

class button : public Widget
{

public:

	button(std::string const &id, Widget *parent) : Widget(id, parent) {}

};
