/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** OpusException
*/

#ifndef OPUSEXCEPTION_HPP_
#define OPUSEXCEPTION_HPP_

#include "Error.hpp"

class OpusException : public Error {
	public:
		OpusException(const std::string &message = "Opus Error", const std::string &component = "Opus Codec") : Error(message, component) {}
};

#endif /* !OPUSEXCEPTION_HPP_ */
