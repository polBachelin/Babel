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

            void setSize(const int &size);
            void setSample(float *);
            void writeToSample(const void *rptr, unsigned long framesPerBuffer, const size_t &nbChannels);
            void readFromSample(void *wptr, unsigned long framesPerBuffer, const size_t &nbChannels);
        protected:
            int _size;
            CircularBuffer _buffer;
            float *_sample;
    };
}

#endif /* !DECODEDSOUND_HPP_ */
