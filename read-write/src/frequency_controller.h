#pragma once

struct DummyFrequencyController 
{
  typedef std::chrono::steady_clock::time_point TimePoint;
  void set(std::type_index, std::chrono::milliseconds, std::chrono::milliseconds) {}
  std::pair<TimePoint, std::type_index> next() { throw -1; }
};

//
template<class TId, class TDuration = std::chrono::milliseconds, class TTimePoint = std::chrono::steady_clock::time_point>
class RandomFrequencyController
{
public:
  typedef TTimePoint TimePoint;

  void set(TId id, TDuration freq, TDuration var)
  {
  }

  std::pair<TimePoint, TId> next()
  {

  }
private:
  std::vector<std::tuple<TId, TDuration, TDuration, TTimePoint>> _table;
};
