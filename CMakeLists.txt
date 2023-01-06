project(MSQ)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BINARY_DIR build)

link_libraries(GLEW GL glfw sndfile portaudio imgui)
include_directories(include)
include_directories(ext)

ADD_CUSTOM_TARGET(link_target ALL
                  COMMAND ${CMAKE_COMMAND} -E create_symlink ../res res)

add_compile_options(-Wall)
add_executable(
    MSQ 
    src/core/Engine.cpp
    src/core/Parameter.cpp
    src/core/Playable.cpp
    src/core/PlayablePipeline.cpp
    src/core/PlayableRack.cpp
    src/core/Sample.cpp
    src/playables/Amp.cpp
    src/playables/GranularSynth.cpp
    src/playables/LoopingSampler.cpp
    src/playables/Sampler.cpp
    ext/imgui_impl_glfw.cpp
    ext/imgui_impl_opengl3.cpp
    mainUi.cpp
)

