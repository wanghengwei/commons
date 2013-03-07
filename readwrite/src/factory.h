#pragma once

#include <typeindex>
#include <tuple>
#include <thread>

template<
  class TB, 
  template<class TProductType> class TProductDefinitionMap, 
  class TFrequencyController
>
class Factory
{
  typedef TProductDefinitionMap<TB> ProductDefinitionMap;
public:

  template<class TD>
  void registerProduct(double freq, double variant)
  {
    typename ProductDefinitionMap::ItemType def(typeid(TD), []() { return new TD; });
    _productDefinitionMap.insert(def);

    _frequencyController.set(def.typeIndex(), freq, variant);
  }

  TB * create()
  {
    //sleep until the time point when the next product should be produced
    typename TFrequencyController::TimePoint nextTimePoint;
    std::type_index productTypeIndex(typeid(TB));
    std::tie(nextTimePoint, productTypeIndex) = _frequencyController.next();
    std::this_thread::sleep_until(nextTimePoint);

    auto def = _productDefinitionMap[productTypeIndex];

    return def.instance();
  }

private:

  ProductDefinitionMap _productDefinitionMap;
  TFrequencyController _frequencyController;

};

