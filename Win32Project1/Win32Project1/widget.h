#pragma once
#include <map>
#include <string>

struct state;
class MousePointer;
struct Point;

//Widget
class Widget
{

public: //Typedef
	typedef std::map<std::string, Widget *> WidgetMap;

private:

	Widget *m_parent;

	WidgetMap m_children;

	std::string m_id;

public:

#pragma region ctor & dtor

	///
	Widget(std::string const& id, Widget *parent = nullptr) : m_id(id), m_parent(parent) {}

	virtual ~Widget() {}

#pragma endregion

	std::string id() const { return m_id; }

	Widget * parent() { return m_parent; }
	Widget const * parent() const { return m_parent; };

	WidgetMap & children() { return m_children; }
	WidgetMap const & children() const { return m_children; }

	Widget & add(Widget *child)
	{
		m_children.insert(std::make_pair(child->id(), child));

		return *this;
	}

#pragma region Recursive methods

	///
	virtual MousePointer & pointer()
	{
		return m_parent->pointer();
	}

	virtual MousePointer const & pointer() const
	{
		return m_parent->pointer();
	}

#pragma endregion

protected:

	Widget * find_widget_at(Point const &);

};