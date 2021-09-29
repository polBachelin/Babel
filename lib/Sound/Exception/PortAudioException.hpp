/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** PortAudioException
*/

#ifndef PORTAUDIOEXCEPTION_HPP_
#define PORTAUDIOEXCEPTION_HPP_

#include "Error.hpp"

class PortAudioException : public Error {
	public:
		PortAudioException(const std::string &message = "Port Audio Error", const std::string &component = "PortAudio API") : Error(message, component) {}
};

#endif /* !PORTAUDIOEXCEPTION_HPP_ */
