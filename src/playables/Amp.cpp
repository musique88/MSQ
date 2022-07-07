#include "playables/Amp.hpp"
#include <imgui.h>

namespace MSQ
{
    Amp::Amp(PlayableInfo plInfo, unsigned int n)
    : Playable(plInfo, n, n) 
    {
        volume_ = 1.f;
    }

    void Amp::processAudio()
    {
        for(unsigned int i = 0; i < plInfo_.bufferSize; i++)
            for(unsigned int j = 0; j < outputChannels_; j ++)
                output_[i * outputChannels_ + j] = input_[i * outputChannels_ + j] * volume_;
    }

    void Amp::sendMidi(int& msg)
    {

    }

    void Amp::render()
    {
        std::string name("Amp##");
        name += std::to_string((unsigned long long)this);
        ImGui::PushID(name.c_str());
        ImGui::Text("Amp");
        ImGui::BeginChild(name.c_str(), ImVec2(0, 24));
        ImGui::SliderFloat("Volume", &volume_, -1.3, 1.3, "%.3f", ImGuiSliderFlags_Logarithmic);
        ImGui::EndChild();
        ImGui::PopID();
    }
}