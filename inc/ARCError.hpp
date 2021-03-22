/*
** EPITECH PROJECT, 2021
** Arcade [WSL: Ubuntu-20.04]
** File description:
** ARCError
*/

#ifndef INC_ARCERROR_HPP_
#define INC_ARCERROR_HPP_

#include <exception>
#include <string>

namespace arc {
class ARCError : public std::exception {
 public:
    explicit ARCError(std::string const &message) : _message(message) {}

    inline virtual const char* what() const noexcept {
        return _message.c_str();
    }

 private:
    std::string _message;
};

class DLLError : public arc::ARCError {
 public:
    explicit DLLError(std::string const &message) : ARCError(message) {}
};
}  // namespace arc

#endif  // INC_ARCERROR_HPP_
