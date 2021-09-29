/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** PortAudioManager
*/

#ifndef PORTAUDIOMANAGER_HPP_
#define PORTAUDIOMANAGER_HPP_

#include "ISoundManager.hpp"
#include "CircularBuffer.hpp"
#include "portaudio.h"
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

        int recordAudio() override;
        int openInputStream();
        
        int playAudio() override;
        void setDefaultInputDevice() override;
        void setDefaultOutputDevice() override;
        std::vector<std::string> getInputDeviceNames() override;
        std::vector<std::string> getOutputDeviceNames() override;
        bool isStreamActive() override;
        bool isMicMuted() override;
        bool isOutputMuted() override;

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
        std::shared_ptr<CircularBuffer> _buffer;
        PaStream *_inputStream;
        PaStream *_outputStream;
        PaStreamParameters _outputParameters;
        PaStreamParameters _inputParameters;
        size_t _nbChannels;
};

#endif /* !PORTAUDIOMANAGER_HPP_ */
