#include "PlayablePipeline.hpp"

namespace MSQ
{
    PlayablePipeline::PlayablePipeline(unsigned int sampleRate, unsigned int bufferSize,
                                       unsigned int inputChannels, unsigned int outputChannels,
                                       unsigned int inputStreams, unsigned int outputStreams)
        : Playable(sampleRate, bufferSize, inputChannels, outputChannels, inputStreams, outputStreams)
    {
        delete output_;
    }

    bool PlayablePipeline::isCorrect() const
    {
        if(playables.empty())
            return false;

        if(!(inputChannels_ == playables.front()->getInputChannels() &&
            inputStreams_ == playables.front()->getInputStreams()))
            return false;

        unsigned int sizeToCheck = playables.size() - 1;
        for(unsigned int i = 0; i < sizeToCheck; i++){
            if(!playables[i]->canOutputTo(*playables[i+1]) || !playables[i]->isCorrect())
                return false;
        }

        if(!(playables.back()->getOutputChannels() == outputChannels_ &&
           playables.back()->getOutputStreams() == outputStreams_) || !playables.back()->isCorrect())
            return false;

        return true;
    }

    void PlayablePipeline::insert(unsigned int at, Playable* playable)
    {
        playables.insert(playables.begin() + at, playable);
        if(at == 0)
            playable->setInput(input_);
        else
            playable->setInput(playables[at-1]->getOutput());

        if(at == playables.size() - 1)
            output_ = playable->getOutput();
        else
            playables[at + 1]->setInput(playable->getOutput());
    }

    void PlayablePipeline::remove(unsigned int at)
    {
        playables.erase(playables.begin() + at);
        if(at == 0)
            playables[0]->setInput(input_);

        if(at == playables.size())
            output_ = playables.back()->getOutput();
        else{
            playables[at]->setInput(playables[at - 1]->getOutput());
            playables[at + 1]->setInput(playables[at]->getOutput());
        }
    }

    void PlayablePipeline::processAudio()
    {
        for(unsigned int i = 0; i < playables.size(); i++)
            playables[i]->processAudio();
    }

    void PlayablePipeline::setInput(const float* input)
    {
        if(!playables.empty())
            playables.front()->setInput(input);
        input_ = input;
    }
}
