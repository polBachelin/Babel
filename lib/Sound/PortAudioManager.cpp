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

PortAudioManager::PortAudioManager() : _buffer(nullptr), _nbChannels(2)
{

    if (Pa_Initialize() != paNoError)
        std::cout << "error on init" << std::endl;
        //TODO add an exception
}

PortAudioManager::~PortAudioManager()
{
    Pa_Terminate();
}

size_t PortAudioManager::getNbChannels() const
{
    return _nbChannels;
}

void PortAudioManager::setNbChannels(const size_t &nbChannels)
{
    _nbChannels = nbChannels;
}

void PortAudioManager::setDefaultInputDevice()
{
    _inputParameters.device = Pa_GetDefaultInputDevice();
}

void PortAudioManager::setDefaultOutputDevice()
{
    _outputParameters.device = Pa_GetDefaultOutputDevice();
}

std::vector<std::string> PortAudioManager::getInputDeviceNames() const
{}

std::vector<std::string> PortAudioManager::getOutputDeviceNames() const
{}

int PortAudioManager::recordCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData)
{
    PortAudioManager *data = static_cast<PortAudioManager *>(userData);
    const float *rptr = static_cast<const float *>(inputBuffer);
    //int finished;

    (void) outputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    // if (data->isMicMuted()) {

    //     std::memset(, SAMPLE_SILENCE, framesPerBuffer * data->_nbChannels * sizeof(float));

    // } else
    data->_buffer->write(rptr, framesPerBuffer * data->_nbChannels * sizeof(float));
    return paContinue;
}

int PortAudioManager::playCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData)
{
    PortAudioManager *data = static_cast<PortAudioManager *>(userData);
    float *wptr = (float *)outputBuffer;
    int finished;
    (void) inputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;
    data->_buffer->read(wptr, framesPerBuffer);
    if (data->_buffer->getBytesLeft() < (int)framesPerBuffer)
        finished = paComplete;  
    else
        finished = paContinue;
    return finished;
}

int PortAudioManager::recordAudio()
{
    PaError err = paNoError;

    if (_buffer == nullptr)
        _buffer = std::make_shared<CircularBuffer>(NUM_SECONDS * SAMPLE_RATE * _nbChannels);
    if( err != paNoError ) 
        return -1;
    err = Pa_StartStream(_inputStream);
    if(err != paNoError) 
        return -1;
    printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);
    while((err = Pa_IsStreamActive(_inputStream)) == 1) {
        Pa_Sleep(1000);
    }
    if(err < 0) 
        return -1;
    err = Pa_CloseStream(_inputStream);
    if(err != paNoError)
        return -1;
    return 0;
}

int PortAudioManager::openInputStream()
{
    PaError err = paNoError;

    _inputParameters.device = Pa_GetDefaultInputDevice();
    if (_inputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default input device.\n");
        return -1;
    }
    _inputParameters.channelCount = 2;
    _inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    _inputParameters.suggestedLatency = Pa_GetDeviceInfo( _inputParameters.device )->defaultLowInputLatency;
    _inputParameters.hostApiSpecificStreamInfo = NULL;
    err = Pa_OpenStream(
            &_inputStream,
            &_inputParameters,
            NULL,
            SAMPLE_RATE,
            FRAMES_PER_BUFFER,
            paClipOff,
            recordCallback,
            this);
    
}

int PortAudioManager::playAudio()
{
    PaError err;

    if (_buffer == nullptr)
        return -1;
    _outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (_outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
        return -1;
    }
    _outputParameters.channelCount = 2;                     /* stereo output */
    _outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
    _outputParameters.suggestedLatency = Pa_GetDeviceInfo(_outputParameters.device )->defaultLowOutputLatency;
    _outputParameters.hostApiSpecificStreamInfo = NULL;

    printf("\n=== Now playing back. ===\n"); fflush(stdout);
    err = Pa_OpenStream(
              &_outputStream,
              NULL, /* no input */
              &_outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              playCallback,
              this);
    if(err != paNoError)
        return -1;
    if(_outputStream) {
        err = Pa_StartStream(_outputStream);
        if(err != paNoError)
            return -1;
        printf("Waiting for playback to finish.\n"); fflush(stdout);
        while( ( err = Pa_IsStreamActive(_outputStream)) == 1)
            Pa_Sleep(100);
        if(err < 0)
            return -1;
        err = Pa_CloseStream(_outputStream);
        if( err != paNoError)
            return -1;
        printf("Done.\n"); fflush(stdout);
    }
    return err;
}

bool PortAudioManager::isStreamActive()
{
    if (Pa_IsStreamActive(_outputStream))
        return 1;
    return 0;
}

bool PortAudioManager::isMicMuted()
{
    return false;
}

bool PortAudioManager::isOutputMuted()
{
    return false;
}