/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** IEncodeManager
*/

#ifndef IENCODEMANAGER_HPP_
#define IENCODEMANAGER_HPP_

#include "DecodedSound.hpp"
#include "EncodedSound.hpp"

class IEncodeManager {
    public:
        virtual Sound::DecodedSound decode(Sound::EncodedSound &sound) = 0;
        virtual Sound::EncodedSound encode(Sound::DecodedSound &sound) = 0;
};

#endif /* !IENCODEMANAGER_HPP_ */
