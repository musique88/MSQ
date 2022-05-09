#include <string>

namespace MSQ 
{
	class Sample 
	{
		float* sample_;
	public:
		unsigned long frameCount;
		unsigned int channelCount;
		unsigned int sampleRate;

		Sample(std::string path);
		~Sample();

		const float* getSample() const;
	};
}
