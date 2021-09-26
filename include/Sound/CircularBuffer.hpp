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
	CircularBuffer(const int &size);
    ~CircularBuffer();

    void cleanup();
    void clear();
    void *getHead() const;
    void *getTail() const;
    int getLen() const;
    int getBytesLeft() const;
    int write(const unsigned char *src, int len);
    int read(unsigned char *src, int len);

  protected:
    unsigned char *_buf;
    int _len;
    int _tailPtr;
    int _headPtr;
    int _bytesLeft;
  private:
};

#endif /* !CIRCULARBUFFER_HPP_ */
