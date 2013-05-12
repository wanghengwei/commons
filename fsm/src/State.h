#pragma once
#include <typeinfo>

struct BaseState 
{
  virtual ~BaseState() {}

  virtual BaseState * Transit(BaseEvent const &) = 0;

virtual void SetContext
};

template<typename MD, typename CTX>
struct TBaseState : BaseState 
{
  typedef CTX Context;

  Context *mContext;

  TBaseState(Context *context = nullptr) : mContext(context)
  {

  }

  BaseState * Transit(BaseEvent const &ev) override
  {
    auto c = this->GetContext();
    delete this;
    auto newState = MD::Reactions::NewStateByEvent(typeid(ev).hash_code());
    newState->SetContext(c);
    return newState;
  }

  Context * GetContext()
  {
    return mContext;
  }

  void SetContext(Context *context)
  {
    mContext = context;
  }
};
