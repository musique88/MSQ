#include "Engine.hpp"
#include <iostream>

namespace MSQ
{
    Engine::Engine()
    {
        if(int err = Pa_Initialize())
            printPaErr(err);
    }

    Engine::~Engine()
    {
        if(int err = Pa_Terminate())
            printPaErr(err);
    }

    void Engine::setInputParameters(PaDeviceIndex dev, unsigned int channels)
    {
        streamParameters.in.device = dev;
        streamParameters.in.channelCount = channels;
        streamParameters.in.sampleFormat = paFloat32;
        streamParameters.in.suggestedLatency = Pa_GetDeviceInfo(dev)->defaultLowInputLatency;
        streamParameters.in.hostApiSpecificStreamInfo = nullptr;
    }

    void Engine::setOutputParameters(PaDeviceIndex dev, unsigned int channels)
    {
        streamParameters.out.device = dev;
        streamParameters.out.channelCount = channels;
        streamParameters.out.sampleFormat = paFloat32;
        streamParameters.out.suggestedLatency = Pa_GetDeviceInfo(dev)->defaultLowOutputLatency;
        streamParameters.out.hostApiSpecificStreamInfo = nullptr;
    }

    void Engine::start(unsigned int sampleRate, unsigned int framesPerBuffer)
    {
        mainPipeline = new PlayablePipeline(sampleRate,
                                            framesPerBuffer,
                                            streamParameters.in.channelCount,
                                            streamParameters.out.channelCount);
        int err = Pa_OpenStream(&stream_,
                      &streamParameters.in,
                      &streamParameters.out,
                      sampleRate,
                      framesPerBuffer,
                      paNoFlag,
                      &Engine::callback,
                      this);
        if(err)
            printPaErr(err);
        if((err = Pa_StartStream(stream_)))
            printPaErr(err);
    }

    void Engine::stop()
    {
        if(int err = Pa_CloseStream(stream_))
            printPaErr(err);
    }

    void Engine::printPaErr(int err) const
    {
        std::cerr << "Portaudio error no " << std::to_string(err)
                  << " : " << Pa_GetErrorText(err) << std::endl;
    }

    std::vector<const PaDeviceInfo*> getDevices()
    {
        unsigned int deviceCount = Pa_GetDeviceCount();
        std::vector<const PaDeviceInfo*> infos(deviceCount);
        for(unsigned int i = 0; i < deviceCount; i++)
            infos.push_back(Pa_GetDeviceInfo(i));
        return infos;
    }
}
