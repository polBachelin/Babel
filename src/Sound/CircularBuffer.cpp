/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CircularBuffer
*/

#include "CircularBuffer.hpp"
#include <iostream>

CircularBuffer::CircularBuffer(const size_t &size) : _len(size), _headPtr(0), _tailPtr(0), _bytesLeft(size)
{
	if (size != 0) {
	_buf = new unsigned char[size];
	for (std::size_t i = 0; i < size; i++)
		_buf[i] = 0;
	} else
		_buf = nullptr;
}

CircularBuffer::~CircularBuffer()
{
	// if (_buf)
	// 	delete [] _buf;
}

void CircularBuffer::cleanup()
{}

void CircularBuffer::clear()
{
	for (std::size_t i = 0; i < _len; i++) {
		_buf[i] = 0;
	}
	_tailPtr = 0;
	_headPtr = 0;
}

void *CircularBuffer::getHead() const
{
	return &_buf[_headPtr];
}

void *CircularBuffer::getTail() const
{
	return &_buf[_tailPtr];
}

int CircularBuffer::getLen() const
{
	return _len;
}

int CircularBuffer::getBytesLeft() const
{
	return _bytesLeft;
}

int CircularBuffer::size() const
{
	return _len - _bytesLeft;
}

bool CircularBuffer::NoMoreBytes()
{
	if (_bytesLeft == 0)
		return true;
	return false;
}

int CircularBuffer::write(const void *src, size_t len)
{
	if (src == nullptr || len == 0 || _bytesLeft <= 0)
		return 0;
	const unsigned char *t = static_cast<const unsigned char *>(src);
	for (size_t i = 0; i < len; i++) {
		_buf[_headPtr] = t[i];
		_headPtr = (_headPtr + 1) % _len;
	}
	_bytesLeft -= len;
	return len;
}

int CircularBuffer::read(void *src, size_t len)
{
	if (src == nullptr || len <= 0 || _bytesLeft == (int)_len)
		return 0;
	unsigned char *t = static_cast<unsigned char *>(src);
	for (size_t i = 0; i < len; i++) {
		t[i] = _buf[_tailPtr];
		_tailPtr = (_tailPtr + 1) % _len;
	}
	_bytesLeft += len;
	return len;
}