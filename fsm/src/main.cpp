#include <string>
#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

struct event
{

};

struct click_button_event : public event {};

struct other_event : public event {};

struct state
{

  virtual ~state()
  {

  }

  virtual void on_process(event const &)
  {

  }
};

struct red_bg_state : public state 
{

  void on_process(click_button_event const &)
  {
    cout << "change background to blue\n";
  }

};

struct blue_bg_state : public state 
{

  template<typename E>
  static void on_process(E const &)
  {

  }

  template<>
  static void on_process<click_button_event>(click_button_event const &)
  {
    cout << "button clicked\n";
  }

};



template<typename States, typename Current>
struct state_machine
{

  template<typename Event>
  static void process(Event const &e)
  {
    Current::on_process(e);
  }

};

struct nil {};

template<typename H, typename T>
struct sv
{
  typedef H head;
  typedef T tail;

};


template<typename V, int N>
struct get_tail
{
  typedef typename get_tail<typename V::tail, N - 1>::type type;
};

template<typename V>
struct get_tail<V, 0>
{
  typedef V type;
};

template<typename V, int N>
struct get
{
  typedef typename get_tail<V, N>::type::head type;
};

#define V2(A1, A2) sv<A1, sv<A2, nil>>
#define V3(A1, A2, A3) sv<A1, sv<A2, sv<A3, nil>>>

int main(int, char *[])
{

  typedef state_machine<V2(blue_bg_state, red_bg_state), blue_bg_state> M;
  M::process(click_button_event());
  return 0;

}
