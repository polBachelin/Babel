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

#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)

namespace Sound {
    class DecodedSound {
        public:
            DecodedSound(const int &size);
            ~DecodedSound();

            int getFrameIndex() const;
            int getMaxFrameIndex() const;
            int getSize() const;
            float *getSample() const;

            void setFrameIndex(const int &f);
            void setMaxFrameIndex(const int &f);
            void setSize(const int &size);
            void setSample(float *);
            int writeToSample(float *rptr, unsigned long framesPerBuffer, const size_t &nbChannels);
        protected:
            int _frameIndex;
            int _maxFrameIndex;
            int _size;
            float *_sample;
    };
}

#endif /* !DECODEDSOUND_HPP_ */
