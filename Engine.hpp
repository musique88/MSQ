#pragma once

#include <portaudio.h>
#include "PlayablePipeline.hpp"
#include <string>

namespace MSQ
{
	class Engine
	{
		void printPaErr(int err) const;
		static int callback(const void *input,
					 void *output,
					 unsigned long frameCount,
					 const PaStreamCallbackTimeInfo *timeInfo,
					 PaStreamCallbackFlags statusFlags,
					 void *userData);
		PaStream* stream_;
		struct {PaStreamParameters in; PaStreamParameters out;} streamParameters;
		unsigned int sampleRate_;
		unsigned int framesPerBuffer_;

	public:
		PlayablePipeline* mainPipeline;
		Engine(unsigned int sampleRate, unsigned int framesPerBuffer);
		~Engine();
		void setInputParameters(PaDeviceIndex dev, unsigned int channels);
		void setOutputParameters(PaDeviceIndex dev, unsigned int channels);
		unsigned int getSampleRate();
		unsigned int getFramesPerBuffer();
		void start();
		void stop();
		std::vector<const PaDeviceInfo*> getDevices();
		static std::string deviceInfoToString(const PaDeviceInfo* info);
	};
}
