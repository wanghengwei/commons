#pragma once
#include "State.h"
#include <cstddef>

template<typename E, typename S, typename Context, void (Context::*SideEffectFunction)()>
struct Transition
{
  typedef E EventType;

  typedef S StateType;

  static void RunSideEffect(Context *obj) { (obj->*SideEffectFunction)(); }
};



template<typename ... T>
struct TVector;

template<typename F, typename S, typename ... T>
struct TVector<F, S, T ...>
{
  static BaseState * NewStateByEvent(size_t hash)
  {
    if (typeid(typename F::EventType).hash_code() == hash) {
      auto newState = new typename F::StateType;
      F::RunSideEffect(newState->GetContext());
      return newState;
    } else {
      return TVector<S, T ...>::NewStateByEvent(hash);
    }
  }
};

template<typename F>
struct TVector<F>
{
  static BaseState * NewStateByEvent(size_t hash)
  {
    if (typeid(typename F::EventType).hash_code() == hash) {
      auto newState = new typename F::StateType;
      F::RunSideEffect(newState->GetContext());
      return newState;
    } else {
      throw std::bad_typeid();
    }
  }

};
