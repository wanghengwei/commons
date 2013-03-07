#pragma once

class Actor;

struct DummyServiceCenter 
{
  void capacity(unsigned int) {}
  void accept(Actor *) {}
};
