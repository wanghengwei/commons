#pragma once

#define _GLIBCXX_USE_NANOSLEEP
#include <thread>

template<typename Product, typename ProductionPlan>
class ProductionLine
{
	public:
		Product * produce()
		{
			auto nt = plan().nextTime();
			std::this_thread::sleep_until(nt);
			plan().forward();
			return new Product;
		}    
		ProductionPlan& plan()
		{
			return _plan;
		}

		std::chrono::steady_clock::time_point nextTime()
		{
			return _plan.nextTime();
		}
	private:
		ProductionPlan _plan;
};

template<typename P, typename... Lines>
class Factory;

template<typename P, typename L>
class Factory<P, L>
{
	public:
		P* produce()
		{
			return _productionLine.produce();
		}

		std::chrono::steady_clock::time_point nextTime()
		{
			return _productionLine.nextTime();
		}
	private:
		L _productionLine;
};

template<typename P, typename H, typename ... T>
class Factory<P, H, T...>
{
	public:
		P * produce() 
		{
			if (_productionLine.plan().nextTime() <= _otherFactories.nextTime()) 
			{
				return _productionLine.produce();
			}
			else
			{
				return _otherFactories.produce();
			}
		}

		std::chrono::steady_clock::time_point nextTime()
		{
			return std::min(_productionLine.nextTime(), _otherFactories.nextTime());
		}

	private:
		H _productionLine;
		Factory<P, T ...> _otherFactories;
};
