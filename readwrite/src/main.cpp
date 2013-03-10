#include "factory.h"
#include "products.h"
#include "productionplans.h"
#include <chrono>
#include <functional>

int main(int, char * [])
{
  Factory<Actor, NeverProduce> rootFactory;

  Factory<Reader, NormalDistribution<std::chrono::milliseconds>> rf;
  Factory<Writer, UniformDistribution<std::chrono::seconds>> wf;

  rootFactory.add(rf);
  rootFactory.add(wf);

  //  ServiceCenter serviceCenter;
  //serviceCenter.capacity(50);

  while (true)
    {
      auto actor = rootFactory.nextProduct();
      //  serviceCenter.accept(actor);
    }
  return 0;
}
