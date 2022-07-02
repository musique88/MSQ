#include "Playable.hpp"
#include <vector>
namespace MSQ
{
    class PlayableRack : public Playable
    {
        void reallocOutput();
        void resetInputs();
        std::vector<Playable*> playables;
    public:
        PlayableRack(PlayableInfo plInfo,
                 unsigned int inputChannels = 2, unsigned int outputChannels = 2,
                 unsigned int inputStreams = 1, unsigned int outputStreams = 1);
        void processAudio() override;
        void sendMidi(int& msq) override;
        void insert(unsigned int at, Playable* playable);
        void remove(unsigned int at);
        bool isCorrect() const override;
    };
}
