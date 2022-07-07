#include "playables/Sampler.hpp"

namespace MSQ
{
    class LoopingSampler : public Sampler
    {
    public:
        LoopingSampler(PlayableInfo plInfo, Sample* sample); 
        void processAudio() override;
    };
}