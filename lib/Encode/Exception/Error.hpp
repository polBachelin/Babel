/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <iostream>

class Error : public std::exception{
	public:
		Error(std::string const &message, std::string const &component = "Unkown");
		std::string const &getComponent() const;
		const char *what() const noexcept override;
	protected:
		std::string _component;
	private:
		std::string _message;
};

#endif /* !ERROR_HPP_ */
