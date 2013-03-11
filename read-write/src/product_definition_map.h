#pragma once

template<class TB>
struct DummyProductDefinition
{
  DummyProductDefinition() {}
  DummyProductDefinition(std::type_index, std::function<TB* ()>) {}
  TB * instance() { throw -1; }
  std::type_index typeIndex() const {}
};

template<class TB>
struct DummyProductDefinitionMap
{
  typedef DummyProductDefinition<TB> ItemType;
  void insert(ItemType const &) {}
  ItemType & operator [] (std::type_index) { throw -1; }
};
