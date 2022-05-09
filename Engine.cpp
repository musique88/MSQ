#include "Engine.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

namespace MSQ
{
	Engine::Engine(unsigned int sampleRate, unsigned int framesPerBuffer)
	: sampleRate_(sampleRate), framesPerBuffer_(framesPerBuffer)
	{
		if(int err = Pa_Initialize())
			printPaErr(err);

		streamParameters.in.device = -1;
		streamParameters.out.device = -1;
	}

	Engine::~Engine()
	{
		if(int err = Pa_Terminate())
			printPaErr(err);
	}

	int Engine::callback(const void *input,
					 void *output,
					 unsigned long frameCount,
					 const PaStreamCallbackTimeInfo *timeInfo,
					 PaStreamCallbackFlags statusFlags,
					 void *userData) 
	{
		Engine* engine = (Engine*)userData;
		float* out = (float*)output;
		engine->mainPipeline->setInput((const float*)input);
		engine->mainPipeline->processAudio();
		float* eOut = engine->mainPipeline->getOutput();
		std::copy(eOut, 
				eOut + frameCount * engine->mainPipeline->getOutputChannels(), 
				out);

		return paContinue;
	}
 

	void Engine::setInputParameters(PaDeviceIndex dev, unsigned int channels)
	{
		streamParameters.in.device = dev;
		streamParameters.in.channelCount = channels;
		streamParameters.in.sampleFormat = paFloat32;
		streamParameters.in.suggestedLatency = Pa_GetDeviceInfo(dev)->defaultLowInputLatency;
		streamParameters.in.hostApiSpecificStreamInfo = nullptr;
	}

	void Engine::setOutputParameters(PaDeviceIndex dev, unsigned int channels)
	{
		streamParameters.out.device = dev;
		streamParameters.out.channelCount = channels;
		streamParameters.out.sampleFormat = paFloat32;
		streamParameters.out.suggestedLatency = Pa_GetDeviceInfo(dev)->defaultLowOutputLatency;
		streamParameters.out.hostApiSpecificStreamInfo = nullptr;
	}

	void Engine::start()
	{
		mainPipeline = new PlayablePipeline(sampleRate_,
											framesPerBuffer_,
											streamParameters.in.channelCount,
											streamParameters.out.channelCount);
		PaStreamParameters* in = streamParameters.in.device == -1 ? nullptr : &streamParameters.in;
		PaStreamParameters* out = streamParameters.out.device == -1 ? nullptr : &streamParameters.out;

		int err = Pa_OpenStream(&stream_,
					  in,
					  out,
					  sampleRate_,
					  framesPerBuffer_,
					  paNoFlag,
					  &Engine::callback,
					  this);
		if(err)
			printPaErr(err);
		if((err = Pa_StartStream(stream_)))
			printPaErr(err);
	}

	void Engine::stop()
	{
		if(int err = Pa_CloseStream(stream_))
			printPaErr(err);
	}

	void Engine::printPaErr(int err) const
	{
		std::cerr << "Portaudio error no " << std::to_string(err)
				  << " : " << Pa_GetErrorText(err) << std::endl;
	}

	std::vector<const PaDeviceInfo*> Engine::getDevices()
	{
		unsigned int deviceCount = Pa_GetDeviceCount();
		std::vector<const PaDeviceInfo*> infos;
		for(unsigned int i = 0; i < deviceCount; i++)
			infos.push_back(Pa_GetDeviceInfo(i));
		return infos;
	}

	std::string Engine::deviceInfoToString(const PaDeviceInfo* info)
	{
		std::stringstream ss;
		ss << info->name << 
			"\n\tIN: " << info->maxInputChannels << 
			"\n\tOUT: " << info->maxOutputChannels <<
			"\n\tSample Rate: " << info->defaultSampleRate <<
			"\n\tHost: " << Pa_GetHostApiInfo(info->hostApi)->name << 
			"\n\tDefault Low Input Latency: " << info->defaultLowInputLatency <<
			"\n\tDefault Low Output Latency: " << info->defaultLowOutputLatency <<
			"\n\tDefault High Input Latency: " << info->defaultHighInputLatency <<
			"\n\tDefault High Output Latency: " << info->defaultHighOutputLatency << "\n";
		return ss.str();
	}
}
