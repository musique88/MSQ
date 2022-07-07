#!/bin/bash

clang++ *.cpp ext/*.cpp src/core/*.cpp src/playables/*.cpp -g -lGLEW -lGL -lglfw -lsndfile -lportaudio -limgui -Iinclude