#include "PlayableRack.hpp"
#include <cstring>

namespace MSQ
{
    PlayableRack::PlayableRack(PlayableInfo plInfo,
                 unsigned int inputChannels, unsigned int outputChannels,
                 unsigned int inputStreams, unsigned int outputStreams)
        : Playable(plInfo, inputChannels, outputChannels, inputStreams, outputStreams)
    {}

    void PlayableRack::reallocOutput()
    {
        delete output_;
        output_ = new float[plInfo_.bufferSize * outputChannels_ * outputStreams_];
    }

    void PlayableRack::resetInputs()
    {
        for(unsigned int i = 0; i < playables.size(); i++)
            playables[i]->setInput(&input_[i * plInfo_.bufferSize * inputChannels_]);
    }

    void PlayableRack::insert(unsigned int at, Playable* playable)
    {
        outputStreams_++;
        inputStreams_++;
        playable->setParent(this);
        playables.insert(playables.begin() + at, playable);
        resetInputs();
        reallocOutput();
    }

    void PlayableRack::remove(unsigned int at)
    {
        outputStreams_--;
        inputStreams_--;
        playables[at]->setParent(nullptr);
        playables.erase(playables.begin() + at);
        resetInputs();
        reallocOutput();
    }

    void PlayableRack::processAudio()
    {
        for(Playable* playable : playables)
            playable->processAudio();
        for(unsigned int i = 0; i < playables.size(); i++)
            std::memcpy(&output_[i * plInfo_.bufferSize * outputChannels_],
                        playables[i]->getOutput(),
                        plInfo_.bufferSize * outputChannels_ * sizeof(float));
    }

    bool PlayableRack::isCorrect() const
    {
        for(Playable* playable : playables)
            if(!playable->isCorrect())
                return false;
        if(playables.empty())
            return false;
        return true;
    }

	void PlayableRack::sendMidi(int& msg)
	{
		(void)msg;
	}
}
