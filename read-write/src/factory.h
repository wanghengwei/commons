#pragma once

template<
  typename Product, 
  typename ProductionPlan
>
class ProductionLine
{
public:


private:
};

template<typename P, typename H, typename ... T>
class Factory
{
public:

  P * produce()
  {
    if (_productionLine.plan().next() < _otherFactories.next()) 
      {
	return _productionLine.
      }

  }

private:
  H _productionLine;
  Factory<T ...> _otherFactories;
};
