#include <string>

namespace MSQ 
{
	class Sample 
	{
		float* sample_;
		unsigned long frameCount_;
		unsigned int channelCount_;
		unsigned int sampleRate_;

	public:
		Sample(std::string path);
		~Sample();

		unsigned long getFrameCount() const;
		unsigned int getChannelCount() const;
		unsigned int getSampleRate() const;
		const float* getSample() const;
	};
}
