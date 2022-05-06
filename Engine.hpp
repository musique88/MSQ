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

	public:
		PlayablePipeline* mainPipeline;
		Engine();
		~Engine();
		void setInputParameters(PaDeviceIndex dev, unsigned int channels);
		void setOutputParameters(PaDeviceIndex dev, unsigned int channels);
		void start(unsigned int sampleRate, unsigned int framesPerBuffer);
		void stop();
		std::vector<const PaDeviceInfo*> getDevices();
		static std::string deviceInfoToString(const PaDeviceInfo* info);
	};
}
