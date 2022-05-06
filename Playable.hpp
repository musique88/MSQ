
namespace MSQ
{
	class Playable
	{
	protected:
		unsigned int sampleRate_;
		unsigned int bufferSize_;

		unsigned int inputChannels_;
		unsigned int outputChannels_;
		unsigned int inputStreams_;
		unsigned int outputStreams_;

		float* output_;
		const float* input_;
	public:
		Playable(unsigned int sampleRate, unsigned int bufferSize,
				 unsigned int inputChannels = 2, unsigned int outputChannels = 2,
				 unsigned int inputStreams = 1, unsigned int outputStreams = 1);

		virtual void setInput(const float* input);
		float* getOutput() const;
		const unsigned int& getInputChannels() const;
		const unsigned int& getOutputChannels() const;
		const unsigned int& getInputStreams() const;
		const unsigned int& getOutputStreams() const;

		bool canOutputTo(const Playable& playable) const;
		virtual bool isCorrect() const;
		virtual void processAudio() = 0;
		virtual void sendMidi(int& msg) = 0;
	};
}
