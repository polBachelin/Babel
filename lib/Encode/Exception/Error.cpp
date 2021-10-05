/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Error
*/

#include "Error.hpp"

Error::Error(std::string const &message, std::string const &component)
    : _component(component), _message(message)
{
}

const char *Error::what() const noexcept
{
    return this->_message.c_str();
}

std::string const &Error::getComponent() const
{
    return this->_component;
}