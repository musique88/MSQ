#include "Sample.hpp"
#include <sndfile.hh>

namespace MSQ
{
	Sample::Sample(std::string path)
	{
		SndfileHandle f(path);
		frameCount = f.frames();
		channelCount = f.channels();
		sampleRate = f.samplerate();

		sample_ = new float[frameCount * channelCount];

		f.readf(sample_, frameCount);
	}

	Sample::~Sample()
	{
		delete sample_;
	}

	const float* Sample::getSample() const
	{
		return sample_;
	}
}
