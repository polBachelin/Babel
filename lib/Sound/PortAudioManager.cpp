/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** PortAudioManager
*/

#include "PortAudioManager.hpp"

#define PA_SAMPLE_TYPE paFloat32
#define SAMPLE_SILENCE  (0.0f)

bool PortAudioManager::_init = false;

PortAudioManager::PortAudioManager() : 
_inputBuffer(nullptr), _outputBuffer(nullptr), _inputSample(nullptr), _outputSample(nullptr), _inputStream(nullptr), _outputStream(nullptr), _inputChannels(2), _outputChannels(2), _outputIndex(0), _inputIndex(0), _micMute(false), _outputMute(false)
{
    if (!PortAudioManager::_init) {
        if (Pa_Initialize() != paNoError)
            std::cout << "error on init" << std::endl;
            //TODO add an exception
        PortAudioManager::_init = true;
    }
    allocateBuffers();
    loadDefaultDevices();
    loadApi();
}

PortAudioManager::~PortAudioManager()
{
    std::cout << "Ending PortAudio API\n";
    if (isInputStreamActive())
        closeInputStream();
    if (isOutputStreamActive())
        closeOutputStream();
    Pa_Terminate();
}

void PortAudioManager::setMicMute(bool mute)
{
    _micMute = mute;
}

bool PortAudioManager::isMicMuted()
{
    return _micMute;
}

void PortAudioManager::setOutputMute(bool mute)
{
    _outputMute = mute;
}

bool PortAudioManager::isOutputMuted()
{
    return _outputMute;
}

int PortAudioManager::getSampleRate()
{
    return SAMPLE_RATE;
}

size_t PortAudioManager::getOutputChannels() const
{
    return _outputChannels;
}

size_t PortAudioManager::getInputChannels() const
{
    return _inputChannels;
}

void PortAudioManager::setInputChannels(const size_t &nbChannels)
{
    _inputChannels = nbChannels;
}

void PortAudioManager::setDefaultInputDevice()
{
    _inputParameters.device = Pa_GetDefaultInputDevice();
    if (_inputParameters.device == paNoDevice) {
        throw PortAudioException("No default input devices found");
    }
}

void PortAudioManager::setDefaultOutputDevice()
{
    _outputParameters.device = Pa_GetDefaultOutputDevice();
    if (_outputParameters.device == paNoDevice)
        throw PortAudioException("No default output devices found");
}

std::vector<std::string> PortAudioManager::getInputDeviceNames() const
{}

std::vector<std::string> PortAudioManager::getOutputDeviceNames() const
{}

void PortAudioManager::allocateBuffers()
{
    int inputSize = NUM_SECONDS * SAMPLE_RATE * _inputChannels * sizeof(float);
    int outputSize = NUM_SECONDS * SAMPLE_RATE * _outputChannels * sizeof(float);

    if (_inputBuffer)
        _inputBuffer.release();
    if (_outputBuffer)
        _outputBuffer.release();
    if (outputSize > 0)
        _outputBuffer = std::make_unique<CircularBuffer>(outputSize);
    else
        _outputBuffer = nullptr;
    if (inputSize > 0)
        _inputBuffer = std::make_unique<CircularBuffer>(inputSize);
    else
        _inputBuffer = nullptr;
    if (_inputSample)
        delete [] _inputSample;
    _inputSample = new float[inputSize];
    std::memset(_inputSample, 0, inputSize);
    if (_outputSample)
        delete [] _outputSample;
    _outputSample = new float[outputSize];
    std::memset(_outputSample, 0, outputSize);
}

void PortAudioManager::loadApi()
{
    loadDefaultDevices();
    openInputStream();
    openOutputStream();
    startInputStream();
    startOutputStream();
}

void PortAudioManager::loadDevices(const int &inputChannels, const int &outputChannels)
{
    _inputParameters.channelCount = inputChannels;
    _inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    _inputParameters.suggestedLatency = Pa_GetDeviceInfo(_inputParameters.device)->defaultLowInputLatency;
    _inputParameters.hostApiSpecificStreamInfo = NULL;

    _outputParameters.channelCount = outputChannels;
    _outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
    _outputParameters.suggestedLatency = Pa_GetDeviceInfo(_outputParameters.device )->defaultLowOutputLatency;
    _outputParameters.hostApiSpecificStreamInfo = NULL;
}

void PortAudioManager::loadDefaultDevices()
{
    setDefaultOutputDevice();
    setDefaultInputDevice();
    loadDevices(2, 2);
}

int PortAudioManager::openInputStream()
{
    if (_inputStream) {
        closeInputStream();
    }
    _inputStream = nullptr;
    Pa_OpenStream(
            &_inputStream,
            &_inputParameters,
            NULL,
            SAMPLE_RATE,
            FRAMES_PER_BUFFER,
            paNoFlag,
            recordCallback,
            this);
    return 0;
}

int PortAudioManager::openOutputStream()
{    
    if (_outputStream) {
        closeOutputStream();
    }
    _outputStream = nullptr;
    PaError err = Pa_OpenStream(
                    &_outputStream,
                    NULL, /* no input */
                    &_outputParameters,
                    SAMPLE_RATE,
                    FRAMES_PER_BUFFER,
                    paNoFlag,      /* we won't output out of range samples so don't bother clipping them */
                    playCallback,
                    this);
    if (err != paNoError) {
        std::cout << "[PortAudio] : Could not open output stream" << std::endl;
    }
    return 0;
}

bool PortAudioManager::isInputStreamActive()
{
    if (_inputStream)
        return 1;
    return 0;
}

bool PortAudioManager::isOutputStreamActive()
{
    if (_outputStream)
        return 1;
    return 0;
}

void PortAudioManager::startInputStream()
{
    PaError err;

    if (_inputStream) {
        err = Pa_StartStream(_inputStream);
        if (err != paNoError)
            throw PortAudioException("Could not start input Stream");
    }
}

void PortAudioManager::startOutputStream()
{
    PaError err;

    if (_outputStream) {
        err = Pa_StartStream(_outputStream);
        if (err != paNoError)
            throw PortAudioException("Could not start output stream");
    }
}

void PortAudioManager::closeOutputStream()
{
    PaError err;

    if (_outputStream) {
        err = Pa_AbortStream(_outputStream);
        if (err != paNoError)
            std::cerr << "Could not abort output stream" << std::endl;
        err = Pa_CloseStream(_outputStream);
        if (err != paNoError)
            std::cerr << "Could not close output stream" << std::endl;
    }
}

void PortAudioManager::closeInputStream()
{
    PaError err;

    if (_inputStream) {
        err = Pa_AbortStream(_inputStream);
        if (err != paNoError)
            std::cerr << "Could not abort input stream" << std::endl;
        err = Pa_CloseStream(_inputStream);
        if (err != paNoError)
            std::cerr << "Could not close input stream" << std::endl;
    }
}

int PortAudioManager::getBytesInInput()
{
    return _inputBuffer->size();
}

int PortAudioManager::retrieveInputBytes(float *sample, size_t len)
{
    if (!sample)
        return 0;
    return _inputBuffer->read(sample, len * _inputChannels * sizeof(float));
}

void PortAudioManager::feedBytesToOutput(float *sample, unsigned long len)
{
    std::memcpy(_outputSample, sample, len * _outputChannels * sizeof(float));
    _outputBuffer->write(sample, len * _outputChannels * sizeof(float));
}

int PortAudioManager::recordCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData)
{
    PortAudioManager *data = static_cast<PortAudioManager *>(userData);
    const float *rptr = static_cast<const float *>(inputBuffer);

    (void) outputBuffer;
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;
    
    if (data->isMicMuted() || inputBuffer == NULL) {
        std::memset(data->_inputSample, 0, framesPerBuffer * data->_inputChannels * sizeof(float));
        data->_inputBuffer->write(data->_inputSample, framesPerBuffer * data->_inputChannels * sizeof(float));
    } else {
        std::memcpy(data->_inputSample, rptr, framesPerBuffer * data->_inputChannels * sizeof(float));
        data->_inputBuffer->write(rptr, framesPerBuffer * data->_inputChannels * sizeof(float));
    }
    return paContinue;
}

int PortAudioManager::playCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData)
{
    PortAudioManager *data = static_cast<PortAudioManager *>(userData);
    float *wptr = static_cast<float *>(outputBuffer);
    size_t frameSize = framesPerBuffer * data->_outputChannels * sizeof(float);
    size_t outputSize = data->_outputBuffer->size();
    size_t toRead;

    (void) inputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    if (data->_outputBuffer->size() == 0) {
        std::memset(wptr, 0, framesPerBuffer * (data->_outputChannels * sizeof(float)));
        return paContinue;
    }
    if (outputSize > frameSize)
        toRead = frameSize;
    else
        toRead = outputSize;
    data->_outputBuffer->read(data->_outputSample, toRead);
    std::memcpy(wptr, data->_outputSample, frameSize);
    return paContinue;
}
