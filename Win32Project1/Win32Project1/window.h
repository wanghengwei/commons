#pragma once
#include "cursor.h"
#include <map>

class window
{
	window *m_parent;

	std::map<int, window *> m_children;

public:
	window(window *parent = nullptr);

	virtual ~window() {}

	virtual cursor_t & cursor() { return m_parent->cursor(); }

	virtual cursor_t const & cursor() const { return m_parent->cursor(); }

	virtual window * parent() { return m_parent; }

	virtual window const * parent() const { return m_parent; };

	virtual void render(HDC, PAINTSTRUCT const &);

	virtual bool is_hot() const { return false; }
};