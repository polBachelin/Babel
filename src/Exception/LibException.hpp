/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** LibException
*/

#ifndef LIBEXCEPTION_HPP_
#define LIBEXCEPTION_HPP_

#include <Error.hpp>

class LibException : public Error {
	public:
		LibException(std::string const &message = "library error", std::string const &component = "Library") : Error(message, component) {}
};

#endif /* !LIBEXCEPTION_HPP_ */
