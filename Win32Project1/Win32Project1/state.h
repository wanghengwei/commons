#pragma once
#include "Events.h"
#include <functional>
#include <typeinfo>
class Widget;

struct state
{
	Widget *hot_widget;

	Widget *active_widget;

	int background_index;

	HBRUSH pre_defined_background[2];

	state() : hot_widget(nullptr), active_widget(nullptr), background_index(0)
	{
		pre_defined_background[0] = CreateSolidBrush(RGB(0, 255, 255));
		pre_defined_background[1] = CreateSolidBrush(RGB(255, 0, 0));
	}
};

typedef std::function<void ()> Output;

class OldStateMachine
{
public:
	virtual Output Transit(PaintEvent const &)
	{
		return Output();
	}

	virtual Output Transit(ReSizedEvent const &)
	{
		return Output();
	}

};




struct BaseState
{
	virtual ~BaseState() {}
	virtual BaseState * Transit(BaseEvent const &ev) = 0;
	virtual void OnEnter() {}
};
struct NilTransition 
{
	static BaseState * Dispatch(size_t hash)
	{
		throw std::bad_typeid();
	}
};
template<typename F, typename T = NilTransition>
struct TVector
{
	static BaseState * Dispatch(size_t hash)
	{
		if (typeid(typename F::EventType).hash_code() == hash) {
			auto newState = new F::StateType;
			F::OnEnter(newState);
			return newState;
		} else {
			return T::Dispatch(hash);
		}
	}
};



template<typename E, typename S, void (S::*EnterAction)() = &S::OnEnter>
struct Transition
{
	typedef E EventType;
	typedef S StateType;

	static void OnEnter(S *obj)
	{
		(obj->*EnterAction)();
	}
};

template<typename MD>
struct TBaseState : BaseState
{
	BaseState * Transit(BaseEvent const &ev) override
	{
		delete this;
		auto newState = MD::Reactions::Dispatch(typeid(ev).hash_code());

		return newState;
	}
};

struct StateMachine
{
	BaseState *mCurrentState;
	StateMachine(BaseState *state = nullptr) : mCurrentState(state) {}

	void Transit(BaseEvent const &ev)
	{
		mCurrentState = mCurrentState->Transit(ev);
	}
};