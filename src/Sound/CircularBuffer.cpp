/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CircularBuffer
*/

#include "CircularBuffer.hpp"

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
	if (_buf)
		delete [] _buf;
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

int CircularBuffer::write(const unsigned char *src, size_t len)
{
	if (src == nullptr || len == 0 || _bytesLeft <= 0)
		return 0;
	if ((int)len > _bytesLeft)
		len = _bytesLeft;
	if (len > _len - _headPtr) {
		int newLen = _len - _headPtr;
		std::memcpy(_buf + _headPtr, src, newLen);
		std::memcpy(_buf, src + newLen, len - newLen);
	} else
		std::memcpy(_buf + _headPtr, src, len);
	_headPtr = (_headPtr + len) % _len;
	_bytesLeft -= len;
	return len;
}

int CircularBuffer::read(unsigned char *src, size_t len)
{
	if (src == nullptr || len <= 0 || _bytesLeft == (int)_len)
		return 0;
	if (len > _len - _bytesLeft)
		len = _len - _bytesLeft;
	if (len > _len - _tailPtr) {
		int newLen = _len - _tailPtr;
		std::memcpy(_buf, src + _tailPtr, newLen);
		std::memcpy(_buf + newLen, src, len - newLen);
	} else
		std::memcpy(_buf, src + _tailPtr, len);
	_tailPtr = (_tailPtr + len) % _len;
	_bytesLeft += len;
	return len;
}