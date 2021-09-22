/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** DecodedSound
*/

#include "DecodedSound.hpp"

using namespace Sound;

DecodedSound::DecodedSound()
{
}

DecodedSound::~DecodedSound()
{
}

int DecodedSound::getFrameIndex() const
{
    return _frameIndex;
}

int DecodedSound::getMaxFrameIndex() const
{
    return _maxFrameIndex;
}
int DecodedSound::getSize() const
{
    return _size;
}

std::vector<float> DecodedSound::getSample() const
{
    return _sample;
}

void DecodedSound::setFrameIndex(const int &f)
{
    _frameIndex = f;
}

void DecodedSound::setMaxFrameIndex(const int &f)
{
    _maxFrameIndex = f;
}

void DecodedSound::setSize(const int &size)
{
    _size = size;
}

void DecodedSound::setSample(const std::vector<float> &s)
{
    _sample = s;
}