/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ISoundManager
*/

#ifndef ISOUNDMANAGER_HPP_
#define ISOUNDMANAGER_HPP_

#include "DecodedSound.hpp"

class ISoundManager {
    public:
        virtual Sound::DecodedSound recordAudio() = 0;
        virtual int playAudio(Sound::DecodedSound &sound) = 0;
        virtual Sound::DecodedSound getSound() const = 0;
        // virtual bool isRecordMuted() = 0;
        // virtual bool isAudioMuted() = 0;
        virtual bool isStreamActive() = 0;
};

#endif /* !ISOUNDMANAGER_HPP_ */
