#include "playables/Sampler.hpp"

#include <imgui.h>
#include <iostream>
#include <cstring>
#include <algorithm>

namespace MSQ
{
    Sampler::Sampler(PlayableInfo plInfo, Sample* sample)
    :Playable(plInfo, 0, sample->getChannelCount(), 0, 1) {
        sample_ = sample;
        sampleRateRatio_ = (float)sample_->getSampleRate() / (float)plInfo_.sampleRate;

        speed_ = 0.5f;
        positionInSample_ = 0;
    }

    // TODO clean
    void Sampler::processAudio()
    {
        unsigned int framesToFill = plInfo_.bufferSize;

        unsigned int i = 0;

        int sampleDifference = sample_->getFrameCount() -
            (framesToFill * speed_ * sampleRateRatio_ + positionInSample_);

        unsigned int sampleEnd;

        if (speed_ < 0) {
            sampleDifference = -(framesToFill * speed_ * sampleRateRatio_ + positionInSample_) / (speed_ * sampleRateRatio_);
        }
        sampleEnd = std::max(0, std::min(sampleDifference, (int)framesToFill));


        for(; i < sampleEnd; i++) 
            for(unsigned int j = 0; j < outputChannels_; j++)
                output_[i * outputChannels_ + j] = 
                    sample_->getSample()[((unsigned int)(i * speed_ * sampleRateRatio_) + positionInSample_) * outputChannels_ + j];
        
        for(; i < framesToFill; i++)
            for(unsigned int j = 0; j < outputChannels_; j++)
                output_[i * outputChannels_ + j] = 0;

        int nextPos = positionInSample_ + framesToFill * speed_ * sampleRateRatio_;
        positionInSample_ = nextPos;
        if (nextPos >= sample_->getFrameCount())
            positionInSample_ = sample_->getFrameCount() - 1;
        if (nextPos < 0)
            positionInSample_ = 0;
    }

    const Sample* Sampler::getSample() const
    {
        return sample_;
    }

    const float Sampler::getSpeed() const
    {
        return speed_;
    }

    const unsigned int Sampler::getPositionInSample() const
    {
        return positionInSample_;
    }

    void Sampler::setSpeed(float speed)
    {
        speed_ = speed;
    }

    void Sampler::setPositionInSample(int position)
    {
        if(position < 0)
            positionInSample_ = (position % sample_->getFrameCount()) + sample_->getFrameCount();
        else 
            positionInSample_ = position % sample_->getFrameCount();
    }

    void Sampler::sendMidi(int& msg)
    {

    } 

    void Sampler::render()
    {
        std::string name("Sampler##");
        name += std::to_string((unsigned long long)this);
        ImGui::PushID(name.c_str());
        ImGui::Text("Sampler");
        ImGui::BeginChild(name.c_str(), ImVec2(0, 50));
        ImGui::SliderInt("Position", (int*)&positionInSample_, 0, sample_->getFrameCount());
        ImGui::SliderFloat("Speed", &speed_, -2, 2);
        ImGui::EndChild();
        ImGui::PopID();
    }
}