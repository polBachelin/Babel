/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** PortAudioManager
*/

#include "PortAudioManager.hpp"

#define PA_SAMPLE_TYPE paFloat32
#define SAMPLE_SILENCE  (0.0f)

extern "C"
{
    std::shared_ptr<ISoundManager> entryPoint()
    {
        return std::make_shared<PortAudioManager>();
    }
}

PortAudioManager::PortAudioManager()
{
    Pa_Initialize();
}

PortAudioManager::~PortAudioManager()
{
    Pa_Terminate();
}

int PortAudioManager::recordCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData)
{
    paData *data = (paData *)userData;
    const float *rptr = (const float *)inputBuffer;
    float *wptr = &data->recordedSample[data->frameIndex * NUM_CHANNELS];
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;
    long framesToCalc;
    long i;
    int finished;
    
    (void)outputBuffer; /* Prevent unused variable warnings. */
    (void)timeInfo;
    (void)statusFlags;
    (void)userData;
    if( framesLeft < framesPerBuffer ) {
        framesToCalc = framesLeft;
        finished = paComplete;
    } else {
        framesToCalc = framesPerBuffer;
        finished = paContinue;
    }
    if( inputBuffer == NULL ) {
        for( i=0; i<framesToCalc; i++ ) {
            *wptr++ = SAMPLE_SILENCE;  /* left */
            if( NUM_CHANNELS == 2 ) 
                *wptr++ = SAMPLE_SILENCE;  /* right */
        }
    } else {
        for( i=0; i<framesToCalc; i++ ) {
            *wptr++ = *rptr++;  /* left */
            if( NUM_CHANNELS == 2 ) 
                *wptr++ = *rptr++;  /* right */
        }
    }
    data->frameIndex += framesToCalc;
    return finished;
}

int PortAudioManager::playCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData)
{}

int PortAudioManager::recordAudio()
{
    PaError err;

    _sound.setMaxFrameIndex(NUM_SECONDS * SAMPLE_RATE);
    _inputParameters.device = Pa_GetDefaultInputDevice();
    if (_inputParameters.device == paNoDevice) {
        std::cout << "Error : No default input device" << std::endl;
        return -1;
    }
    _inputParameters.channelCount = NUM_CHANNELS;
    _inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    _inputParameters.suggestedLatency = Pa_GetDeviceInfo(_inputParameters.device)->defaultLowInputLatency;
    _inputParameters.hostApiSpecificStreamInfo = NULL;
    err = Pa_OpenStream(&_stream, &_inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, recordCallback, &_sound);
    if (err != paNoError) {
        std::cout << "Error : could not open Stream" << std::endl;
        return -1;
    }
    err = Pa_StartStream(_stream);
    if (err != paNoError) {
        std::cout << "Error : could not start Stream" << std::endl;
        return -1;
    }
    while ( (err = Pa_IsStreamActive(_stream)) == 1) {
        Pa_Sleep(100);
    }
    err = Pa_CloseStream(_stream);
    if (err != paNoError) {
        std::cout << "Error : could not close Stream" << std::endl;
        return -1;
    }
    return 0;
}

int PortAudioManager::playAudio()
{}

bool PortAudioManager::isStreamActive()
{
    if (Pa_IsStreamActive(_stream))
        return 1;
    return 0;
}