#include "Renderable.hpp"
#include "Parameter.hpp"
#include <unordered_map>
#include <string>

namespace MSQ
{
    struct PlayableInfo{
        unsigned int sampleRate;
        unsigned int bufferSize;
    };

    class Playable : public Renderable
    {
    protected:
        Playable* parent_;
        std::unordered_map<std::string, Parameter> parameters_;

        PlayableInfo plInfo_;

        unsigned int inputChannels_;
        unsigned int outputChannels_;
        unsigned int inputStreams_;
        unsigned int outputStreams_;

        float* output_;
        const float* input_;

        void registerParam(std::string name, Parameter param);
    public:
        Playable(PlayableInfo plInfo,
                unsigned int inputChannels = 2, 
				unsigned int outputChannels = 2,
                unsigned int inputStreams = 1, 
				unsigned int outputStreams = 1);

        Playable(Playable* parent,
                unsigned int inputChannels = 2, 
				unsigned int outputChannels = 2,
                unsigned int inputStreams = 1, 
				unsigned int outputStreams = 1);

        void setParent(Playable* parent);
        const Playable* getParent() const;

        float getParameter(std::string name);
        float setParameter(std::string name, float value);

        virtual void setInput(const float* input);
        float* getOutput() const;
        const unsigned int& getInputChannels() const;
        const unsigned int& getOutputChannels() const;
        const unsigned int& getInputStreams() const;
        const unsigned int& getOutputStreams() const;

        bool canOutputTo(const Playable& playable) const;
        virtual bool isCorrect() const;
        virtual void processAudio() = 0;
        virtual void sendMidi(int& msg) = 0;
		virtual void render() = 0;
    };
}
