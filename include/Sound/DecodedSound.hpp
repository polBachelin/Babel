/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** DecodedSound
*/

#ifndef DECODEDSOUND_HPP_
#define DECODEDSOUND_HPP_

#include <array>
#include <vector>
#include <iostream>
#include "CircularBuffer.hpp"
#include <memory>

#define SAMPLE_RATE  (48000)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (5)

namespace Sound {
    class DecodedSound {
        public:
            DecodedSound(const int &size, const int &alignedSize = 0);
            ~DecodedSound();

            int getSize() const;
            int getBytesLeft() const;
            float *getSample() const;
            float *getAlignedBuffer() const;
            void clearAligned(size_t bytesRead, unsigned long len);
            size_t write(const void *rptr, unsigned long len);
            size_t read(void *wptr, unsigned long len);
            size_t alignSample(unsigned long len);
        protected:
            int _size;
            std::shared_ptr<CircularBuffer> _buffer;
            float *_alignedBuffer = nullptr;
    };
}

#endif /* !DECODEDSOUND_HPP_ */
