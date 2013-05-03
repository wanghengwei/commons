#pragma once
#include "widget.h"

class button : public widget
{

public:

	button(std::string const &id, widget *parent) : widget(id, parent) {}

};
