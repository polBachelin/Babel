/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** DecodedSound
*/

#include "DecodedSound.hpp"

using namespace Sound;

DecodedSound::DecodedSound(const int &frameIndex, const int &maxFrame, const int &size)
: _frameIndex(frameIndex), _maxFrameIndex(maxFrame), _size(size)
{
    _sample = new float[size];
}

DecodedSound::~DecodedSound()
{
    delete [] _sample;
}

int DecodedSound::getFrameIndex() const
{
    return _frameIndex;
}

int DecodedSound::getMaxFrameIndex() const
{
    return _maxFrameIndex;
}
int DecodedSound::getSize() const
{
    return _size;
}

float *DecodedSound::getSample() const
{
    return _sample;
}

void DecodedSound::setFrameIndex(const int &f)
{
    _frameIndex = f;
}

void DecodedSound::setMaxFrameIndex(const int &f)
{
    _maxFrameIndex = f;
}

void DecodedSound::setSize(const int &size)
{
    _size = size;
}

void DecodedSound::setSample(float *s)
{
    _sample = s;
}

void DecodedSound::writeToSample(float *rptr, unsigned long framesPerBuffer, const size_t &nbChannels)
{
    unsigned long framesLeft = _maxFrameIndex - _frameIndex;
    long framesToCalc;
    long i;
    int finished;
    float *wptr = &_sample[_frameIndex * nbChannels];

    if (framesLeft < framesPerBuffer) {
        framesToCalc = framesLeft;
        finished = 1;
    } else {
        framesToCalc = framesPerBuffer;
        finished = 0;
    }
    if (rptr == NULL) {
        for (i = 0; i < framesToCalc; i++) {
            *_sample++ = 0.0f;
            if (nbChannels == 2)
                *_sample++ = 0.0f;
        }
    } else {
        for (i = 0; i < framesToCalc; i++) {
            *_sample++ = *rptr++;
            if (nbChannels == 2)
                *_sample++ = *rptr++;
        }
    }
    _frameIndex += framesToCalc;
}