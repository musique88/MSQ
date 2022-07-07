#include "core/Playable.hpp"

namespace MSQ
{
    class Amp : public Playable
    {
        float volume_;

    public:
        Amp(PlayableInfo plInfo, unsigned int n);
        void processAudio() override;
        void sendMidi(int& msg) override;
        void render() override;
    };  
} 
