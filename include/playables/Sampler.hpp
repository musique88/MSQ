#include "core/Playable.hpp"
#include "core/Sample.hpp"

namespace MSQ
{
	class Sampler : public Playable
	{
	protected:
		Sample* sample_;

		float speed_;
		float sampleRateRatio_;
		unsigned int positionInSample_;

	public:
		Sampler(PlayableInfo plInfo, Sample* sample);
		virtual void processAudio() override;
		const Sample* getSample() const;

		const float getSpeed() const;
		const unsigned int getPositionInSample() const;

		void setSpeed(float speed);
		void setPositionInSample(int position);

		void sendMidi(int& msg) override;
		void render() override;
	};
}
