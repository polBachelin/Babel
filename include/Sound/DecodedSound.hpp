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

#define SAMPLE_RATE  (48000)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (3)
#define NUM_CHANNELS    (2)

namespace Sound {
    class DecodedSound {
        public:
            DecodedSound(const int &size);
            ~DecodedSound();

            int getSize() const;
            int getBytesLeft() const;
            float *getSample() const;

            void write(const void *rptr, unsigned long framesPerBuffer);
            void read(void *wptr, unsigned long framesPerBuffer);
            void alignSample(unsigned long framesPerBuffer);
        protected:
            int _size;
            CircularBuffer _buffer;
            float *_alignedBuffer;
    };
}

#endif /* !DECODEDSOUND_HPP_ */
