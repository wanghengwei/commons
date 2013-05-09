#include <boost/statechart/transition.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
namespace sc = boost::statechart;

#define CTOR(name) name() { cout << "Enter " << #name << endl; }	\
  ~name() { cout << "Exit " << #name << endl; }

struct HalfPressEvent : sc::event<HalfPressEvent> {};

struct ReleaseEvent : sc::event<ReleaseEvent> {};

struct NotShooting;

struct Camera : sc::state_machine<Camera, NotShooting>
{
  CTOR(Camera)

  void f(HalfPressEvent const &) { cout << "f()" << endl; }
};

struct Shooting : sc::simple_state<Shooting, Camera>
{
  CTOR(Shooting)

  typedef sc::transition<ReleaseEvent, NotShooting> reactions;
};

struct NotShooting : sc::simple_state<NotShooting, Camera>
{
  CTOR(NotShooting)

  typedef sc::transition<HalfPressEvent, Shooting, Camera, &Camera::f> reactions;
};

int main()
{

  Camera camera;

  camera.initiate();

  camera.process_event(HalfPressEvent());

  camera.terminate();

  return 0;
}
