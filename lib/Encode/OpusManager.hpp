/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** OpusManager
*/

#ifndef OPUSMANAGER_HPP_
#define OPUSMANAGER_HPP_

#include "IEncodeManager.hpp"
#include "opus.h"

class OpusManager : public IEncodeManager {
	public:
		OpusManager();
		~OpusManager();

		Sound::DecodedSound decode(Sound::EncodedSound &sound) override;
		Sound::EncodedSound encode(Sound::DecodedSound &sound) override;
	protected:
	private:
};

#endif /* !OPUSMANAGER_HPP_ */
