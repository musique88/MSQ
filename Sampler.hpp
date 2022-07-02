#include "Playable.hpp"
#include "Sample.hpp"

namespace MSQ
{
	class Sampler : public Playable
	{
		Sample* sample_;

		float speed_;
		float sampleRateRatio_;
		unsigned int positionInSample_;

	public:
		Sampler(PlayableInfo plInfo, Sample* sample);
		void processAudio() override;
		void sendMidi(int& msg) override;
		void render() override;
	};
}
