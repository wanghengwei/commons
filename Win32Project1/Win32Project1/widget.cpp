#include "stdafx.h"
#include "widget.h"
#include "shape.h"
#include <algorithm>

using namespace std;

void widget::render(HDC hdc, PAINTSTRUCT const &ps)
{
	for (auto p : m_children) {
		p.second->render(hdc, ps);
	}
}

widget * widget::find_widget_at(point_t const &p)
{
	//assume THIS widget is hot. We must find out that which child is hot.
	auto it = find_if(children().begin(), children().end(), 
		[p](children_map::value_type const &v) 
	{
		auto s = dynamic_cast<shape *>(v.second);
		return s && s->contains(p);
	});

	if (it == children().end()) {
		return this;
	}
	else {
		return it->second->find_widget_at(p);
	}
}