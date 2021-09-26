/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** DecodedSound
*/

#include "DecodedSound.hpp"

using namespace Sound;

DecodedSound::DecodedSound(const int &size)
: _frameIndex(0), _maxFrameIndex(0), _size(size)
{
	if (size != 0) {
		_sample = new float[size];
		for (int i = 0; i < size; i++)
			_sample[i] = 0;
	} else
		_sample = nullptr;
}

DecodedSound::~DecodedSound()
{
	//if (_sample != nullptr)
		//delete [] _sample;
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
	float *wptr = &_sample[_frameIndex * nbChannels];

	if (framesLeft < framesPerBuffer) {
		framesToCalc = framesLeft;
	} else {
		framesToCalc = framesPerBuffer;
	}
	if (rptr == NULL) {
		for (i = 0; i < framesToCalc; i++) {
			*wptr++ = 0.0f;
			if (nbChannels == 2)
				*wptr++ = 0.0f;
		}
	} else {
		for (i = 0; i < framesToCalc; i++) {
			*wptr++ = *rptr++;
			if (nbChannels == 2)
				*wptr++ = *rptr++;
		}
	}
	_frameIndex += framesToCalc;
}

void DecodedSound::readFromSample(float *wptr, unsigned long framesPerBuffer, const size_t &nbChannels)
{
	float *rptr = &_sample[_frameIndex * nbChannels];
	unsigned int i;
	unsigned int framesLeft = _maxFrameIndex - _frameIndex;

	if (framesLeft < framesPerBuffer) {
		for (i = 0; i < framesLeft; i++) {
			*wptr++ = *rptr++;
			if (nbChannels == 2)
				*wptr++ = *rptr++;
		}
		for (; i < framesPerBuffer; i++) {
			*wptr++ = 0;
			if (nbChannels == 2)
				*wptr++ = 0;
		}
		_frameIndex += framesLeft;
	} else {
		for (i = 0; i < framesPerBuffer; i++) {
			*wptr++ = *rptr++;
			if (nbChannels == 2)
				*wptr++ = *rptr++;
		}
		_frameIndex += framesPerBuffer;
	}
}