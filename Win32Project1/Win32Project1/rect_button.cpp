#include "stdafx.h"
#include "rect_button.h"
#include "state.h"

void rect_button::react_state()
{
	widget::react_state();

	//���ȫ��״̬���������active widget���Լ�����ô����ȫ��״̬�е�background
	if (global_state().active_widget == this) {
		global_state().background_index ^= 1;
		global_state().active_widget = nullptr;
	}
}

void rect_button::render(HDC hdc, PAINTSTRUCT const &ps)
{

	RECT rect(shadow_face());
	FillRect(hdc, &rect, m_shadow_brush);

	HBRUSH brush = global_state().hot_widget == this ? m_hot_brush : m_nor_brush;
	rect = normal_face();
	FillRect(hdc, &rect, brush);

	widget::render(hdc, ps);
}
