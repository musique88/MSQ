#include "core/Sample.hpp"
#include <sndfile.hh>

namespace MSQ
{
	Sample::Sample(std::string path)
	{
		SndfileHandle f(path);
		frameCount_ = f.frames();
		channelCount_ = f.channels();
		sampleRate_ = f.samplerate();
		path_ = path;

		sample_ = new float[frameCount_ * channelCount_];

		f.readf(sample_, frameCount_);
	}

	Sample::~Sample()
	{
		delete sample_;
	}

	const std::string Sample::getPath() const
	{
		return path_;
	}

	const float* Sample::getSample() const
	{
		return sample_;
	}

	const unsigned long Sample::getFrameCount() const
	{
		return frameCount_;
	}

	const unsigned int Sample::getChannelCount() const 
	{
		return channelCount_;
	}

	const unsigned int Sample::getSampleRate() const 
	{
		return sampleRate_;
	}
}
