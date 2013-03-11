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
    auto x = std::min_element(_children.begin(), _children.end()/*, TODO*/);
    if (x->plan().next() > this->plan().next()) {
      std::this_thread::sleep_until(plan().next());
      return produce();
    } 
    else {
      std::this_thread::sleep_until(x->plan().next());
      return x->produce();
    }
  }
private:
};

