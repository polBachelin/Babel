/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** FileException
*/

#ifndef FILEEXCEPTION_HPP_
#define FILEEXCEPTION_HPP_

#include "Error.hpp"

class FileException : public Error {
	public:
		FileException(std::string const &message = "file error", std::string const &component = "File") : Error(message, component) {}
};

#endif /* !FILEEXCEPTION_HPP_ */
