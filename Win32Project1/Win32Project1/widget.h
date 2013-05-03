#pragma once
#include "mouse_pointer.h"
#include <map>
#include <string>

struct state;

//widget
class widget
{
public:
	typedef std::map<std::string, widget *> children_map;

private:
	widget *m_parent;

	children_map m_children;

	std::string m_id;

public:
	///
	widget(std::string const& id, widget *parent = nullptr) : m_id(id), m_parent(parent)
	{
		
	}

	virtual ~widget() {}

	///
	std::string id() const { return m_id; }

	widget * parent() { return m_parent; }

	widget const * parent() const { return m_parent; };

	children_map & children() { return m_children; }

	children_map const & children() const { return m_children; }

	widget & add(widget *child)
	{
		m_children.insert(std::make_pair(child->id(), child));

		return *this;
	}

	///
	virtual mouse_pointer & pointer()
	{
		return m_parent->pointer();
	}

	virtual mouse_pointer const & pointer() const
	{
		return m_parent->pointer();
	}

	virtual state & global_state()
	{
		return m_parent->global_state();
	}

	///
	virtual void react_state()
	{
		for (auto c : m_children)
		{
			c.second->react_state();
		}
	}

	virtual void render(HDC, PAINTSTRUCT const &);

protected:

	widget * find_widget_at(point_t const &);

};