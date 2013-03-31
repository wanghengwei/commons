#pragma once
#include <future>
#include <iostream>
#include <thread>

class Actor;

struct ServiceCenter 
{
  void capacity(unsigned int) {}
  void accept(Actor * actor) 
  {
	  //std::cout << "begin work..." << std::endl;
	  new std::thread(std::bind(&Actor::work, actor));
	  //std::cout << "async..." << std::endl;
  }
};
