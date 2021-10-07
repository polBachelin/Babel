/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** DecodedSound
*/

#include "DecodedSound.hpp"

using namespace Sound;

DecodedSound::DecodedSound(const int &size, const int &alignedSize) : _size(size)
{
	_alignedBuffer = new float[alignedSize];
	std::memset(_alignedBuffer, 0, alignedSize);
	_buffer = std::make_shared<CircularBuffer>(size);
}

DecodedSound::~DecodedSound()
{
	std::cout << "$$$ Destroying decoded sound\n";
	//if (_sample != nullptr)
		//delete [] _sample;
}

int DecodedSound::getSize() const
{
	return _size;
}

int DecodedSound::getBytesLeft() const
{
	return _buffer->getBytesLeft();
}

float *DecodedSound::getAlignedBuffer() const
{
	return _alignedBuffer;
}

void DecodedSound::clearAligned(size_t bytesRead, unsigned long len)
{
	std::memset(_alignedBuffer + bytesRead, 0, len);
}

size_t DecodedSound::write(const void *rptr, unsigned long len)
{
	return _buffer->write(rptr, len);
}

size_t DecodedSound::read(void *wptr, unsigned long len)
{
	return _buffer->read(wptr, len);
}

size_t DecodedSound::alignSample(unsigned long len)
{
	int ok = _buffer->read(_alignedBuffer, len);
	return ok;
}
