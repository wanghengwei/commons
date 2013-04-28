#include "stdafx.h"
#include "window.h"

using namespace std;

window::window(window *parent) : m_parent(parent)
{
	if (m_parent) {
		m_parent->m_children[0] = this;
	}
}

void window::render(HDC hdc, PAINTSTRUCT const &ps)
{
	for (auto p : m_children) {
		p.second->render(hdc, ps);
	}
}