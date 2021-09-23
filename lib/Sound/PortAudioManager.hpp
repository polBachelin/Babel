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

        Sound::DecodedSound recordAudio() override;
        int playAudio(Sound::DecodedSound &sound) override;
        Sound::DecodedSound getSound() const override;
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

        size_t getNbChannels() const;
        void setNbChannels(const size_t &nbChannels);
        static void writeToBuffer(float *rptr, unsigned long framesPerBuffer);

    protected:
        paData _data;
        std::shared_ptr<Sound::DecodedSound> _sound;
        PaStream *_stream;
        PaStreamParameters _outputParameters;
        PaStreamParameters _inputParameters;
        size_t _nbChannels;
};

#endif /* !PORTAUDIOMANAGER_HPP_ */
