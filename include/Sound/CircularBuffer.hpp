/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CircularBuffer
*/

#ifndef CIRCULARBUFFER_HPP_
#define CIRCULARBUFFER_HPP_

#include <cstddef>
#include <cstring>
#include <cstdint>

class CircularBuffer {
  public:
	  CircularBuffer(const size_t &size);
    ~CircularBuffer();

    void cleanup();
    void clear(size_t len);
    bool NoMoreBytes();
    void *getHead() const;
    void *getTail() const;
    unsigned char *getRawBuf() const;
    int getLen() const;
    int getBytesLeft() const;
    int size() const;
    int write(const void *src, size_t len);
    int read(void *src, size_t len);
    CircularBuffer &operator=(const CircularBuffer &buf);
  protected:
    unsigned char *_buf;
    size_t _len;
    int _headPtr;
    int _tailPtr;
    int _bytesLeft;
};

#endif /* !CIRCULARBUFFER_HPP_ */
