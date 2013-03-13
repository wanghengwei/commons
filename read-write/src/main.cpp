#include "factory.hpp"
#include "products.h"
#include "plans.h"
#include "service_center.h"
#include <iostream>

using namespace std;

int main(int, char * [])
{
  typedef ProductionLine<Reader, NormalDistribution<std::chrono::milliseconds, 2000, 1000>> ReaderProductionLine;
  typedef ProductionLine<Writer, NormalDistribution<std::chrono::milliseconds, 50000, 100>> WriterProductionLine;
  Factory<Actor, ReaderProductionLine, WriterProductionLine> factory;

  ServiceCenter serviceCenter;
  //serviceCenter.capacity(50);

  while (true)
    {
      auto actor = factory.produce();
      serviceCenter.accept(actor);
	  //cout << "1" << endl;
    }
  return 0;
}
