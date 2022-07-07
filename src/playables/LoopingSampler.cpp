#include "playables/LoopingSampler.hpp"

namespace MSQ
{
    LoopingSampler::LoopingSampler(PlayableInfo plInfo, Sample* sample)
    : Sampler(plInfo, sample)
    {}

    void LoopingSampler::processAudio()
    {
        unsigned int framesToFill = plInfo_.bufferSize;

        for(unsigned int i = 0; i < framesToFill; i++) 
            for(unsigned int j = 0; j < outputChannels_; j++)
                output_[i * outputChannels_ + j] = 
                    sample_->getSample()[(
                        ((unsigned int)((i * speed_ * sampleRateRatio_) + positionInSample_ + sample_->getFrameCount()) 
                        % sample_->getFrameCount()))
                        * outputChannels_ + j];
        positionInSample_ = ((unsigned int)((((int)framesToFill * speed_ * sampleRateRatio_) + positionInSample_) 
                        + sample_->getFrameCount()) % sample_->getFrameCount());
       
    }
}