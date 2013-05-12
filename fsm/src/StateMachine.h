#pragma once

template<typename S>
struct StateMachine
{
  BaseState *mCurrentState;
  StateMachine() 
  {

  }

  virtual ~StateMachine() {}

  virtual void Init()
  {
    mCurrentState = new S(this);
  }

  void Transit(BaseEvent const & ev)
  {
    mCurrentState = mCurrentState->Transit(ev);
  };
};
