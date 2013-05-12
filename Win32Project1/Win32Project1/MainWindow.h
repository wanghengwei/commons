#pragma once
#include "window.h"
#include "Widget.h"
#include "MousePointer.h"
#include "state.h"
#include "Rectangle.h"
#include "Color.h"
#include "Events.h"
#include "RenderAdaptor.h"
#include <functional>

class MainWindow : public Window<MainWindow>, public Widget, public StateMachine, protected Rectangle
{

	struct State : TBaseState<State>
	{
		typedef TVector<
			Transition<PaintEvent, State>
		> Reactions;

		Color Background;
	};

	MousePointer *mPointer;

public:

	MainWindow(HINSTANCE app_inst);

	~MainWindow()
	{
		//DeleteObject(m_background);
	}

	MousePointer & pointer() override
	{
		return *mPointer;
	}

	MousePointer const & pointer() const override
	{
		return *mPointer;
	}

	//state & global_state()
	//{
	//	return *this;
	//}

	//void Transit(PaintEvent const& e) override
	//{
	//	//Don't change current state
	//	return [&e, this]() 
	//	{
	//		this->Draw(e.Renderer(), this->mState.Background); 

	//		for (auto w : children()) {
	//			auto sm = dynamic_cast<OldStateMachine *>(w.second);
	//			if (sm) {
	//				auto output = sm->Transit(e);
	//				output();
	//			}
	//		}
	//	};
	//}

	//void Transit(ReSizedEvent const &e) override
	//{
	//	return [&e, this]()
	//	{
	//		this->SetHeight(e.Height).SetWidth(e.Width);
	//	};
	//};

#pragma region Win32窗体事件处理

	//void on_paint(RenderAdaptor * renderer) override
	//{
	//	//PAINTSTRUCT ps;
	//	//HDC hdc = BeginPaint(handle(), &ps);
	//	//render(hdc, ps);
	//	//EndPaint(handle(), &ps);

	//	//临时这么做
	//	Height(Window::GetHeight());
	//	Width(Window::GetWidth());

	//	auto output = Transit(PaintEvent(renderer));

	//	output();
	//}

	//void on_mouse_move(int x, int y) override
	//{
	//	pointer().Position(x, y);
	//	//hot_widget = find_widget_at(pointer().Position());
	//}

	//void on_mouse_left_down(int x, int y) override
	//{
	//	pointer().Position(x, y);
	//	//active_widget = find_widget_at(Point(x, y));
	//}

#pragma endregion

};

