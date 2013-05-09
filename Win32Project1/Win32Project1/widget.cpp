#include "stdafx.h"
#include "Widget.h"
#include "MousePointer.h"
#include "Shape.h"
#include <algorithm>

using namespace std;

Widget * Widget::find_widget_at(Point const &p)
{
	//assume THIS Widget is hot. We must find out that which child is hot.
	auto it = find_if(children().begin(), children().end(), 
		[p](WidgetMap::value_type const &v) 
	{
		auto s = dynamic_cast<Shape *>(v.second);
		return s && s->Contains(p);
	});

	if (it == children().end()) {
		return this;
	}
	else {
		return it->second->find_widget_at(p);
	}
}