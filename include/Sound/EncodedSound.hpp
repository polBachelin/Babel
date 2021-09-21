/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** EncodedSound
*/

#ifndef ENCODEDSOUND_HPP_
#define ENCODEDSOUND_HPP_

#include <vector>

namespace Sound {
    class EncodedSound {
        public:
            EncodedSound();
            ~EncodedSound();

        protected:
            std::vector<unsigned char> _buffer;
            int _size;
        private:
    };
}

#endif /* !ENCODEDSOUND_HPP_ */
