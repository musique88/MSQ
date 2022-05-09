#include "Playable.hpp"

namespace MSQ
{
	class Sampler : public Playable
	{
		float* sample;
	public:
		Sampler(float* sample, unsigned long sampleSize);

	};
}
