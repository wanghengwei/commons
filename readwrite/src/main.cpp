#define _GLIBCXX_USE_NANOSLEEP 1
#include "factory.h"
#include "reader.h"
#include "writer.h"
#include "product_definition_map.h"
#include "frequency_controller.h"
#include "service_center.h"

int main(int, char * [])
{
  Factory<Actor, DummyProductDefinitionMap, DummyFrequencyController> factory;

  factory.registerProduct<Reader>(1, 0.5);
  factory.registerProduct<Writer>(0.2, 0.1);

  DummyServiceCenter serviceCenter;
  serviceCenter.capacity(50);

  while (true)
    {
      auto user = factory.create();
      serviceCenter.accept(user);
    }
  return 0;
}
