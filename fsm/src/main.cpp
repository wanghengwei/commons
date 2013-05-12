#include "Event.h"
#include "State.h"
#include "Transition.h"
#include "StateMachine.h"
#include <iostream>
#include <typeinfo>

using namespace std;

#define DEFAULT_CTOR_WITH_LOG(name) name() { std::cout << #name << "()\n"; }
#define DEFAULT_DTOR_WITH_LOG(name) ~name() { std::cout << "~" << #name << "()\n"; }



struct AEvent : BaseEvent {};
struct BEvent : BaseEvent {};

struct AState;

struct MyMachine : StateMachine<AState>
{
  void f() { cout << "f()\n"; }
};

struct BState : TBaseState<BState, MyMachine>
{
  typedef TVector<
    Transition<AEvent, AState, MyMachine, &MyMachine::f>, 
    Transition<BEvent, BState, MyMachine, &MyMachine::f>
    > Reactions;

  DEFAULT_CTOR_WITH_LOG(BState);
  DEFAULT_DTOR_WITH_LOG(BState);
};

struct AState : TBaseState<AState, MyMachine>
{

  static void LogStateChanged(BaseState *)
  {
    cout << "Current state changed to be BState\n";
  }

  typedef TVector<
    Transition<AEvent, AState, MyMachine, &MyMachine::f>, 
    Transition<BEvent, BState, MyMachine, &MyMachine::f>
    > Reactions;

  DEFAULT_CTOR_WITH_LOG(AState);

  DEFAULT_DTOR_WITH_LOG(AState);

};





int main()
{

  MyMachine sm;
  sm.Transit(AEvent());
  sm.Transit(BEvent());

  return 0;
}
