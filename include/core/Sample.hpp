#include <string>

namespace MSQ 
{
	class Sample 
	{
		float* sample_;
		unsigned long frameCount_;
		unsigned int channelCount_;
		unsigned int sampleRate_;
		std::string path_;

	public:
		Sample(std::string path);
		~Sample();

		const std::string getPath() const;	
		const unsigned long getFrameCount() const;
		const unsigned int getChannelCount() const;
		const unsigned int getSampleRate() const;
		const float* getSample() const;
	};
}
