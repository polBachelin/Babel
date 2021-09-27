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

class CircularBuffer {
  public:
	  CircularBuffer(const size_t &size);
    ~CircularBuffer();

    void cleanup();
    void clear();
    void *getHead() const;
    void *getTail() const;
    int getLen() const;
    int getBytesLeft() const;
    int write(const unsigned char *src, size_t len);
    int read(unsigned char *src, size_t len);

  protected:
    unsigned char *_buf;
    size_t _len;
    int _headPtr;
    int _tailPtr;
    int _bytesLeft;
  private:
};

#endif /* !CIRCULARBUFFER_HPP_ */
