

#include "factory.h"
#include "products.h"



int main(int, char * [])
{
  typedef ProductionLine<Reader, NormalDistribution<std::chrono::milliseconds>> ReaderProductionLine;
  typedef ProductionLine<Writer, UniformDistribution<std::chrono::seconds>> WriterProductionLine;

  Factory<
    ReaderProductionLine, 
    WriterProductionLine
    > factory;

  //  ServiceCenter serviceCenter;
  //serviceCenter.capacity(50);

  while (true)
    {
      //      auto actor = factory.nextProduct();
      //  serviceCenter.accept(actor);
    }
  return 0;
}
