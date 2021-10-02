/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** IEncodeManager
*/

#ifndef IENCODEMANAGER_HPP_
#define IENCODEMANAGER_HPP_

#include <cstddef>

class IEncodeManager {
    public:
        virtual ~IEncodeManager() = default;
        virtual void setBitRate(const int &bitRate) = 0;
        virtual void setSamplingRate(const int &samplingRate) = 0;
        virtual void setComplexity(const int &complexity) = 0;
        virtual void initDecoder();
        virtual void initEncoder();
        virtual int encode(unsigned char *output, float *input, int frameSize, std::size_t outputSize) = 0;
        virtual int decode(const unsigned char *input, float *output, int frameSize, std::size_t intputSize) = 0;
};

#endif /* !IENCODEMANAGER_HPP_ */
