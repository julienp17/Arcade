/*
** EPITECH PROJECT, 2021
** Arcade [WSL: Ubuntu-20.04]
** File description:
** ARCError
*/

#ifndef LIB_INC_ERROR_HPP_
#define LIB_INC_ERROR_HPP_

#include <exception>
#include <string>

namespace arc {
/** @class Error
 * @brief Standard arcade error
 */
class Error : public std::exception {
 public:
    explicit Error(std::string const &message) : _message(message) {}

    inline virtual const char* what() const noexcept {
        return _message.c_str();
    }

 private:
    std::string _message;
};

/** @class ParseError
 * @brief Errors related to parsing
 */
class ParseError : public Error {
 public:
    explicit ParseError(std::string const &message) : Error(message) {}
};

/** @class DLError
 * @brief Errors related to dynamic libraries
 */
class DLError : public Error {
 public:
    explicit DLError(std::string const &message) : Error(message) {}
};

/** @class DisplayError
 * @brief Errors related to display libraries
 */
class DisplayError : public Error {
 public:
    explicit DisplayError(std::string const &message) : Error(message) {}
};
}  // namespace arc

#endif  // LIB_INC_ERROR_HPP_
