/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** DecodedSound
*/

#include "DecodedSound.hpp"

using namespace Sound;

DecodedSound::DecodedSound(const int &size)
: _size(size), _buffer(size)
{
}

DecodedSound::~DecodedSound()
{
	//if (_sample != nullptr)
		//delete [] _sample;
}

int DecodedSound::getSize() const
{
	return _size;
}

float *DecodedSound::getSample() const
{
	return _sample;
}

int DecodedSound::getBytesLeft() const
{
	return _buffer.getBytesLeft();
}

void DecodedSound::setSize(const int &size)
{
	_size = size;
}

void DecodedSound::setSample(float *s)
{
	_sample = s;
}

void DecodedSound::writeToSample(const void *rptr, unsigned long framesPerBuffer, const size_t &nbChannels)
{
	const unsigned char *t = static_cast<const unsigned char *>(rptr);
	_buffer.write(t, framesPerBuffer);
}

void DecodedSound::readFromSample(void *wptr, unsigned long framesPerBuffer, const size_t &nbChannels)
{
	unsigned char *t = static_cast<unsigned char *>(wptr);
	_buffer.read(t, framesPerBuffer);
}