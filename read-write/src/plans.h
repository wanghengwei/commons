#pragma once
#include <random>
#include <cmath>

template<typename Period, int E = 1000, int V = 500>
class NormalDistribution
{
	public:
		NormalDistribution() : _gen(std::random_device()()), _dist(E, V), _nt(std::chrono::steady_clock::now() + Period((long long)round(_dist(_gen))))
		{
		}

		std::chrono::steady_clock::time_point nextTime()
		{
			return _nt;
		}

		void forward()
		{
			_nt += Period((long long)round(_dist(_gen)));
		}
	private:
		std::minstd_rand _gen;
		std::normal_distribution<> _dist;
		std::chrono::steady_clock::time_point _nt;
};
