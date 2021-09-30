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
	_alignedBuffer = new float[size];
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

int DecodedSound::getBytesLeft() const
{
	return _buffer.getBytesLeft();
}

CircularBuffer DecodedSound::getBuffer() const
{
	return _buffer;
}

float *DecodedSound::getAlignedBuffer() const
{
	return _alignedBuffer;
}

size_t DecodedSound::write(const void *rptr, unsigned long len)
{
	return _buffer.write(rptr, len);
}

size_t DecodedSound::read(void *wptr, unsigned long len)
{
	return _buffer.read(wptr, len);
}

size_t DecodedSound::alignSample(unsigned long len)
{
	int ok = _buffer.read(_alignedBuffer, len);
	return ok;
}