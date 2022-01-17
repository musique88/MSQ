#include "Playable.hpp"
#include <vector>

namespace MSQ
{
    // Made for Linear Chaining
    class PlayablePipeline : public Playable
    {
        std::vector<Playable*> playables;
    public:
        PlayablePipeline(unsigned int sampleRate, unsigned int bufferSize_,
                 unsigned int inputChannels = 2, unsigned int outputChannels = 2,
                 unsigned int inputStreams = 1, unsigned int outputStreams = 1);
        void setInput(const float* input) override;
        void processAudio() override;
        void sendMidi(int& msg) override;
        void insert(unsigned int at, Playable* playable);
        void remove(unsigned int at);
        bool isCorrect() const override;
    };
}
