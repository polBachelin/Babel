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
#define FRAMES_PER_BUFFER (480)
#define NUM_SECONDS     (10)
#define NUM_CHANNELS    (2)

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
        void startInputStream() override;
        void startOutputStream() override;
        void setDefaultInputDevice() override;
        void setDefaultOutputDevice() override;
        std::vector<std::string> getInputDeviceNames() const override;
        std::vector<std::string> getOutputDeviceNames() const override;
        bool isInputStreamActive() override;
        bool isOutputStreamActive() override;
        void setMicMute(bool mute) override;
        bool isMicMuted() override;
        void setOutputMute(bool mute) override;
        bool isOutputMuted() override;
        void closeOutputStream() override;
        void closeInputStream() override;
        int getBytesInInput() override;
        int retrieveInputBytes(float *sample, size_t len) override;
        void feedBytesToOutput(float *sample, unsigned long len) override;
        void loadDefaultDevices() override;
        size_t getInputChannels() const override;
        size_t getOutputChannels() const override;
        int getSampleRate() override;


        void allocateBuffers();
        void loadApi();
        void loadDevices(const int &inputChannels, const int &outputChannels);

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
    

        void setInputChannels(const size_t &nbChannels);
        static void writeToBuffer(float *rptr, unsigned long framesPerBuffer);
    protected:
        paData _data;
        std::unique_ptr<CircularBuffer> _inputBuffer;
        std::unique_ptr<CircularBuffer> _outputBuffer;
        float *_inputSample;
        float *_outputSample;
        PaStream *_inputStream;
        PaStream *_outputStream;
        size_t _inputChannels;
        size_t _outputChannels;
        int _outputIndex;
        int _inputIndex;
        bool _micMute;
        bool _outputMute;
        PaStreamParameters _inputParameters;
        PaStreamParameters _outputParameters;
    private:
        static bool _init;
};

#endif /* !PORTAUDIOMANAGER_HPP_ */
