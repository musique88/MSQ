#include "Playable.hpp"
#include "Sample.hpp"

namespace MSQ
{
	class Sampler : public Playable
	{
		Sample* sample_;
	public:
		Sampler(Sample* sample);
	};
}
