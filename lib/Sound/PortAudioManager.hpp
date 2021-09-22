/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** PortAudioManager
*/

#ifndef PORTAUDIOMANAGER_HPP_
#define PORTAUDIOMANAGER_HPP_

#include "ISoundManager.hpp"
#include "portaudio.h"
#include "DecodedSound.hpp"
#include <iostream>
#include <memory>

class PortAudioManager : public ISoundManager {
    
    typedef struct {
        int frameIndex;
        int maxFrameIndex;
        float *recordedSamples;
    } paData;

    public:
        PortAudioManager();
        ~PortAudioManager();

        int recordAudio() override;
        int playAudio() override;
        bool isStreamActive() override;

        static int recordCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData);
        static int playCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData);
    protected:
        paData *_data;
        Sound::DecodedSound _sound;
        PaStream *_stream;
        PaStreamParameters _outputParameters;
        PaStreamParameters _inputParameters;
};

#endif /* !PORTAUDIOMANAGER_HPP_ */
