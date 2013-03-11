#pragma once


template<
  typename Product, 
  typename ProductionPlan
>
class Factory
{
  typedef Factory<Product, ProductionPlan> _Self;
public:
  template<typename P, typename PP>
  _Self& add(Factory<P, PP> const & child)
  {
    return *this;
  }

  Product * nextProduct()
  {
    auto x = std::min_element(_children.begin(), _children.end());
    IFactory * f = x->nextProducingTime() > this->nextProducingTime() ? this : &*x;
    std::this_thread::sleep_until(f->nextProducingTime());
    f->setNextProduceTime();
    return f->produce();
  }
private:
};

