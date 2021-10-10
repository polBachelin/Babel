/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CircularBuffer
*/

#include "CircularBuffer.hpp"
#include <iostream>

CircularBuffer::CircularBuffer(const int &size) : _len(size), _headPtr(0), _tailPtr(0), _bytesLeft(size)
{
	std::cout << "ALLOCATING BUFFER" << std::endl;
	if (size != 0) {
		_buf = new unsigned char[size];
		std::memset(_buf, 0, size);
	} else
		_buf = nullptr;
}

CircularBuffer::~CircularBuffer()
{
	std::cout << "#### DESTROYING BUFFER" << std::endl;
	// if (_buf)
	// 	delete [] _buf;
}

void CircularBuffer::cleanup()
{}

void CircularBuffer::clear(size_t len)
{
	std::memset(_buf, 0, len);
}

void *CircularBuffer::getHead() const
{
	return &_buf[_headPtr];
}

void *CircularBuffer::getTail() const
{
	return &_buf[_tailPtr];
}

std::size_t CircularBuffer::getLen() const
{
	return _len;
}

int CircularBuffer::getBytesLeft() const
{
	return _bytesLeft;
}

unsigned char *CircularBuffer::getRawBuf() const
{
	return _buf;
}

int CircularBuffer::size() const
{
	return (int)_len - _bytesLeft;
}

bool CircularBuffer::NoMoreBytes()
{
	if (_bytesLeft == 0)
		return true;
	return false;
}

int CircularBuffer::write(const void *src, int len)
{
	if (src == nullptr || len == 0 || _bytesLeft <= 0)
		return 0;
	const unsigned char *t = static_cast<const unsigned char *>(src);
	for (int i = 0; i < len; i++) {
		_buf[_headPtr] = t[i];
		_headPtr = (_headPtr + 1) % _len;
	}
	_bytesLeft -= len;
	if (_bytesLeft <= 0) {
		_bytesLeft = _len;
		_tailPtr = _headPtr;
	}
	return len;
}

int CircularBuffer::read(void *src, int len)
{
	if (src == nullptr || len <= 0 || (int)(_len - _bytesLeft) < len)
		return 0;
	unsigned char *t = static_cast<unsigned char *>(src);
	for (int i = 0; i < len; i++) {
		t[i] = _buf[_tailPtr];
		_tailPtr = (_tailPtr + 1) % _len;
	}
	_bytesLeft += len;
	return len;
}

CircularBuffer &CircularBuffer::operator=(const CircularBuffer &buf)
{
	if (&buf == this)
		return *this;
	if (_len != buf._len) {
		delete [] _buf;
		_buf = new unsigned char[buf._len];
	}
	std::memcpy(_buf, buf._buf, buf._len);
	_len = buf._len;
	_headPtr = buf._headPtr;
	_tailPtr = buf._tailPtr;
	_bytesLeft = buf._bytesLeft;
	return *this;
}