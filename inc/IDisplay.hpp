/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** IDisplay
*/

#ifndef INC_IDISPLAY_HPP_
#define INC_IDISPLAY_HPP_

#include "arcade.hpp"

namespace arc {
class IDisplay {
 public:
    virtual ~IDisplay(void) = 0;

    virtual void createWindow(void) = 0;
    virtual void destroyWindow(void) = 0;
    virtual bool windowIsOpen(void) const = 0;
    virtual void display(void) = 0;
    virtual void clear(void) = 0;
    virtual Input getInput(void) = 0;
};
}  // namespace arc

#endif  // INC_IDISPLAY_HPP_
