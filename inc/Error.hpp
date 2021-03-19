/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <string>

class Error : public std::exception {
 public:
    explicit Error(std::string const &message) : _message(message) {}

    inline virtual const char* what() const noexcept {
        return _message.c_str();
    }

 private:
    std::string _message;
};

class ParseError : public Error {
 public:
    explicit ParseError(std::string const &message) : Error(message) {}
};

#endif /* !ERROR_HPP_ */
