/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** Client description:
** ClientError
*/

#ifndef CLIENTERROR_HPP_
#define CLIENTERROR_HPP_

#include "Error.hpp"

class ClientException : public Error
{
	public:
		ClientException(std::string const &message = "Client error", std::string const &component = "Client") : Error(message, component) {}
};

#endif /* !CLIENTERROR_HPP_ */
