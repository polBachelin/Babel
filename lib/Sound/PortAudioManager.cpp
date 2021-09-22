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
    float *rptr = (float *)inputBuffer;
    float *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;
    long framesToCalc;
    long i;
    int finished;
    
    (void)outputBuffer; /* Prevent unused variable warnings. */
    (void)timeInfo;
    (void)statusFlags;
    (void)userData;
    if(framesLeft < framesPerBuffer) {
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
        PaStreamParameters  inputParameters,
                        outputParameters;
    PaStream*           stream;
    PaError             err = paNoError;
    paData          data;
    int                 i;
    int                 totalFrames;
    int                 numSamples;
    int                 numBytes;
    float              max, val;
    double              average;

    printf("patest_record.c\n"); fflush(stdout);

    data.maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
    data.frameIndex = 0;
    numSamples = totalFrames * NUM_CHANNELS;
    numBytes = numSamples * sizeof(float);
    data.recordedSamples = (float *)malloc(numBytes); /* From now on, recordedSamples is initialised. */
    if( data.recordedSamples == NULL )
    {
        printf("Could not allocate record array.\n");
        return -1;
    }
    for( i=0; i<numSamples; i++ ) data.recordedSamples[i] = 0;

    err = Pa_Initialize();
    if( err != paNoError ) return -1;

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (inputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default input device.\n");
        return -1;
    }
    inputParameters.channelCount = 2;                    /* stereo input */
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    /* Record some audio. -------------------------------------------- */
    err = Pa_OpenStream(
              &stream,
              &inputParameters,
              NULL,                  /* &outputParameters, */
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              recordCallback,
              &data );
    if( err != paNoError ) return -1;

    err = Pa_StartStream( stream );
    if( err != paNoError ) return -1;
    printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);

    while( ( err = Pa_IsStreamActive( stream ) ) == 1 )
    {
        Pa_Sleep(1000);
        printf("index = %d\n", data.frameIndex ); fflush(stdout);
    }
    if( err < 0 ) return -1;

    err = Pa_CloseStream( stream );
    if( err != paNoError ) return -1;

    /* Measure maximum peak amplitude. */
    max = 0;
    average = 0.0;
    for( i=0; i<numSamples; i++ )
    {
        val = data.recordedSamples[i];
        if( val < 0 ) val = -val; /* ABS */
        if( val > max )
        {
            max = val;
        }
        average += val;
    }

    average = average / (double)numSamples;

    printf("sample average = %lf\n", average );
    // PaError err;
    // paData data;

    // data.maxFrameIndex = NUM_SECONDS * SAMPLE_RATE;
    // data.recordedSample = (float *)malloc(NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS * sizeof(float));
    //     for(int i=0; i<NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS; i++ ) data.recordedSample[i] = 0;
    // _inputParameters.device = Pa_GetDefaultInputDevice();
    // if (_inputParameters.device == paNoDevice) {
    //     std::cout << "Error : No default input device" << std::endl;
    //     return -1;
    // }
    // _inputParameters.channelCount = NUM_CHANNELS;
    // _inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    // _inputParameters.suggestedLatency = Pa_GetDeviceInfo(_inputParameters.device)->defaultLowInputLatency;
    // _inputParameters.hostApiSpecificStreamInfo = NULL;
    // err = Pa_OpenStream(&_stream, &_inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, recordCallback, &data);
    // if (err != paNoError) {
    //     std::cout << "Error : could not open Stream" << std::endl;
    //     return -1;
    // }
    // err = Pa_StartStream(_stream);
    // if (err != paNoError) {
    //     std::cout << "Error : could not start Stream" << std::endl;
    //     return -1;
    // }
    // while ((err = Pa_IsStreamActive(_stream)) == 1) {
    //     Pa_Sleep(100);
    // }
    // err = Pa_CloseStream(_stream);
    // if (err != paNoError) {
    //     std::cout << "Error : could not close Stream" << std::endl;
    //     return -1;
    // }
    // return 0;
}

int PortAudioManager::playAudio()
{
    PaError err;

    if (_data->recordedSamples == nullptr)
        return -1;
    _data->frameIndex = 0;
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