/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** PortAudioManager
*/

#ifndef PORTAUDIOMANAGER_HPP_
#define PORTAUDIOMANAGER_HPP_

#include "ISoundManager.hpp"
#include "DecodedSound.hpp"
#include "portaudio.h"
#include "PortAudioException.hpp"
#include <iostream>
#include <memory>

#define SAMPLE_RATE  (48000)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (3)
#define NUM_CHANNELS    (1)

class PortAudioManager : public ISoundManager {
    
    typedef struct {
        int frameIndex;
        int maxFrameIndex;
        float *recordedSamples;
    } paData;

    public:
        PortAudioManager();
        ~PortAudioManager();

        int openInputStream();
        int openOutputStream();
        int recordAudio() override;
        int playAudio() override;
        void setDefaultInputDevice() override;
        void setDefaultOutputDevice() override;
        std::vector<std::string> getInputDeviceNames() const override;
        std::vector<std::string> getOutputDeviceNames() const override;
        bool isInputStreamActive() override;
        bool isOutputStreamActive() override;
        bool isMicMuted() override;
        bool isOutputMuted() override;
        void closeOutputStream() override;
        void closeInputStream() override;

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
        std::shared_ptr<Sound::DecodedSound> _inputBuffer;
        std::shared_ptr<Sound::DecodedSound> _outputBuffer;
        PaStream *_inputStream;
        PaStream *_outputStream;
        size_t _nbChannels;
        PaStreamParameters _inputParameters;
        PaStreamParameters _outputParameters;
};

#endif /* !PORTAUDIOMANAGER_HPP_ */
