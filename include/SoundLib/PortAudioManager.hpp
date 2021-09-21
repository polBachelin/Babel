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

class PortAudioManager : public ISoundManager {
    public:
        PortAudioManager();
        ~PortAudioManager();

        int recordAudio() override;
        int playAudio() override;
        bool isStreamActive() override;

        void recordCallback();
        void playCallback();
    protected:
        DecodedSound _sound;
        PaStream *_stream;
        PaStreamParameters _outputParameters;
        PaStreamParameters _inputParameters;
};

#endif /* !PORTAUDIOMANAGER_HPP_ */
