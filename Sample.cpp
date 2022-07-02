#include "Sample.hpp"
#include <sndfile.hh>

namespace MSQ
{
	Sample::Sample(std::string path)
	{
		SndfileHandle f(path);
		frameCount_ = f.frames();
		channelCount_ = f.channels();
		sampleRate_ = f.samplerate();

		sample_ = new float[frameCount_ * channelCount_];

		f.readf(sample_, frameCount_);
	}

	Sample::~Sample()
	{
		delete sample_;
	}

	const float* Sample::getSample() const
	{
		return sample_;
	}

	unsigned long Sample::getFrameCount() const
	{
		return frameCount_;
	}

	unsigned int Sample::getChannelCount() const 
	{
		return channelCount_;
	}

	unsigned int Sample::getSampleRate() const 
	{
		return sampleRate_;
	}
}
