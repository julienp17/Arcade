/*
** EPITECH PROJECT, 2021
** Arcade [WSL: Ubuntu-20.04]
** File description:
** ARCError
*/

#ifndef INC_ERROR_HPP_
#define INC_ERROR_HPP_

#include <exception>
#include <string>

namespace arc {
class Error : public std::exception {
 public:
    explicit Error(std::string const &message) : _message(message) {}

    inline virtual const char* what() const noexcept {
        return _message.c_str();
    }

 private:
    std::string _message;
};

class ParseError : public Error
{
public:
    explicit ParseError(std::string const &message) : Error(message) {}
};

class DLLError : public Error {
 public:
    explicit DLLError(std::string const &message) : Error(message) {}
};
}  // namespace arc

#endif  // INC_ERROR_HPP_