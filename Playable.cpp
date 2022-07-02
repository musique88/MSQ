#include "Playable.hpp"

namespace MSQ
{
    void Playable::registerParam(std::string name, Parameter param)
    {
        parameters_[name] = param;
    }

    Playable::Playable(PlayableInfo plInfo,
                       unsigned int inputChannels, unsigned int outputChannels,
                       unsigned int inputStreams, unsigned int outputStreams)
        : plInfo_(plInfo),
          inputChannels_(inputChannels), outputChannels_(outputChannels),
          inputStreams_(inputStreams), outputStreams_(outputStreams)
    {
        output_ = new float[plInfo_.bufferSize * outputChannels_ * outputStreams_];
        input_ = nullptr;
        parent_ = nullptr;
    }

    Playable::Playable(Playable* parent,
                       unsigned int inputChannels, unsigned int outputChannels,
                       unsigned int inputStreams, unsigned int outputStreams)
        : Playable(parent->plInfo_,
          inputChannels, outputChannels, inputStreams, outputStreams)
    {
        parent_ = parent;
    }

    void Playable::setParent(Playable* parent)
    {
        parent_ = parent;
    }

    const Playable* Playable::getParent() const
    {
        return parent_;
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
