#include "Sampler.hpp"
#include <cstring>
#include <algorithm>

namespace MSQ
{
    Sampler::Sampler(PlayableInfo plInfo, Sample* sample)
    :Playable(plInfo, 0, sample->getChannelCount(), 0, 1) {
        sample_ = sample;
        sampleRateRatio_ = (float)sample_->getSampleRate() / (float)plInfo_.sampleRate;
        
        speed_ = 1.f;
        positionInSample_ = 0;
    }

    void Sampler::processAudio()
    {
        unsigned int framesToFill = plInfo_.bufferSize;

        unsigned int i = 0;

        int sampleDifference = sample_->getFrameCount() -
            (framesToFill * speed_ * sampleRateRatio_ + positionInSample_);

        unsigned int sampleEnd = std::min(sampleDifference, (int)framesToFill);

        for(; i < framesToFill; i++) 
            for(unsigned int j = 0; j < outputChannels_; j++)
                output_[i * outputChannels_ + j] = 
                    sample_->getSample()[((unsigned int)(i * speed_ * sampleRateRatio_) + positionInSample_) * outputChannels_ + j];
        
        for(; i < framesToFill; i++)
            for(unsigned int j = 0; j < outputChannels_; j++)
                output_[i * outputChannels_ + j] = 0;
    }

    void Sampler::sendMidi(int& msg)
    {

    } 

    void Sampler::render()
    {

    }
}