#include "Playable.hpp"

namespace MSQ
{
    Playable::Playable(unsigned int sampleRate, unsigned int bufferSize,
                       unsigned int inputChannels, unsigned int outputChannels,
                       unsigned int inputStreams, unsigned int outputStreams)
        : sampleRate_(sampleRate), bufferSize_(bufferSize),
          inputChannels_(inputChannels), outputChannels_(outputChannels),
          inputStreams_(inputStreams), outputStreams_(outputStreams)
    {
        output_ = new float[bufferSize_ * outputChannels_ * outputStreams_];
        input_ = nullptr;
    }

    const unsigned int& Playable::getInputChannels() const
    {
        return inputChannels_;
    }

    const unsigned int& Playable::getOutputChannels() const
    {
        return outputChannels_;
    }

    const unsigned int& Playable::getInputStreams() const
    {
        return inputStreams_;
    }

    const unsigned int& Playable::getOutputStreams() const
    {
        return outputStreams_;
    }

    void Playable::setInput(const float* input)
    {
        input_ = input;
    }

    float* Playable::getOutput() const
    {
        return output_;
    }

    bool Playable::canOutputTo(const Playable& playable) const
    {
        return outputChannels_ == playable.inputChannels_ && outputStreams_ == playable.inputStreams_;
    }

    bool Playable::isCorrect() const
    {
        return true;
    }

}
