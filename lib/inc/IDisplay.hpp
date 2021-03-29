/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** IDisplay
*/

#ifndef LIB_INC_IDISPLAY_HPP_
#define LIB_INC_IDISPLAY_HPP_

#include <string>
#include "arcade.hpp"

namespace arc {
/** @class IDisplay
 * @brief Interface for a display Library
 */
class IDisplay {
 public:
    virtual ~IDisplay() = default;

    virtual void createWindow(void) = 0;
    virtual void destroyWindow(void) = 0;
    virtual void display(void) const = 0;
    virtual void clear(void) = 0;
    virtual Input getInput(void) const = 0;
    virtual std::string getName(void) const = 0;
};
}  // namespace arc

#endif  // LIB_INC_IDISPLAY_HPP_
