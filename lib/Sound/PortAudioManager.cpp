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

PortAudioManager::PortAudioManager() : _sound(nullptr), _nbChannels(2)
{

    if (Pa_Initialize() != paNoError)
        std::cout << "error on init" << std::endl;
        //throw execption
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

Sound::DecodedSound PortAudioManager::getSound() const
{
    return *_sound;
}

int PortAudioManager::recordCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData)
{
    PortAudioManager *data = static_cast<PortAudioManager *>(userData);
    float *rptr = (float *)inputBuffer;
    return data->_sound->writeToSample(rptr, framesPerBuffer, data->getNbChannels());
}

int PortAudioManager::playCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData)
{
    paData *data = (paData*)userData;
    float *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    float *wptr = (float *)outputBuffer;
    unsigned int i;
    int finished;
    unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

    (void) inputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    if( framesLeft < framesPerBuffer )
    {
        /* final buffer... */
        for( i=0; i<framesLeft; i++ )
        {
            *wptr++ = *rptr++;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
        }
        for( ; i<framesPerBuffer; i++ )
        {
            *wptr++ = 0;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = 0;  /* right */
        }
        data->frameIndex += framesLeft;
        finished = paComplete;
    }
    else
    {
        for( i=0; i<framesPerBuffer; i++ )
        {
            *wptr++ = *rptr++;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
        }
        data->frameIndex += framesPerBuffer;
        finished = paContinue;
    }
    return finished;
}

int PortAudioManager::recordAudio()
{
    PaError err = paNoError;
    int i;
    int totalFrames;
    int numSamples;
    int numBytes;

    printf("patest_record.c\n"); fflush(stdout);
    if (_sound == nullptr)
        _sound = std::make_shared<Sound::DecodedSound>(NUM_SECONDS * SAMPLE_RATE * _nbChannels);
    _sound->setMaxFrameIndex(NUM_SECONDS * SAMPLE_RATE);

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
              &_stream,
              &_inputParameters,
              NULL,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,
              recordCallback,
              this);
    if( err != paNoError ) 
        return -1;

    err = Pa_StartStream(_stream);
    if(err != paNoError) 
        return -1;
    printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);
    while((err = Pa_IsStreamActive(_stream)) == 1)
    {
        Pa_Sleep(1000);
        std::cout << "index = " << _sound->getFrameIndex() << std::endl;
    }
    if(err < 0) 
        return -1;
    err = Pa_CloseStream(_stream);
    if(err != paNoError)
        return -1;
       double max = 0;
       double average = 0.0;
       for( i=0; i<numSamples; i++ )
       {
           double val = _sound->getSample()[i];
           if( val < 0 ) val = -val; /* ABS */
           if( val > max )
           {
               max = val;
           }
           average += val;
       }
   
       average = average / (double)numSamples;
   
       printf("sample average = %lf\n", average );
    return 0;
}

int PortAudioManager::playAudio(Sound::DecodedSound &sound)
{
    PaError err;

    if (_data.recordedSamples == nullptr)
        return -1;
    _data.frameIndex = 0;
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
              &_stream,
              NULL, /* no input */
              &_outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              playCallback,
              &_data);
    if(err != paNoError)
        return -1;

    if(_stream)
    {
        err = Pa_StartStream(_stream);
        if(err != paNoError)
            return -1;

        printf("Waiting for playback to finish.\n"); fflush(stdout);
        while( ( err = Pa_IsStreamActive(_stream)) == 1)
            Pa_Sleep(100);
        if(err < 0)
            return -1;

        err = Pa_CloseStream(_stream);
        if( err != paNoError)
            return -1;

        printf("Done.\n"); fflush(stdout);
    }
    return err;
}

bool PortAudioManager::isStreamActive()
{
    if (Pa_IsStreamActive(_stream))
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