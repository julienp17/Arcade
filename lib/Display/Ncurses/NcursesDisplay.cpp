/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** NcursesDisplay
*/

#include <iostream>
#include "NcursesDisplay.hpp"

namespace arc {
void NcursesDisplay::createWindow(void) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    mvprintw(50, 50, "hello world");
    refresh();
}

void NcursesDisplay::destroyWindow(void) {
    endwin();
}

void NcursesDisplay::draw(void) const {
    refresh();
}

void NcursesDisplay::clear(void) {
    clear();
}

Input NcursesDisplay::getInput(void) const {
    int c = getch();

    switch (c) {
    case KEY_UP:
        return UP;
    case KEY_DOWN:
        return DOWN;
    case KEY_LEFT:
        return LEFT;
    case KEY_RIGHT:
        return RIGHT;
    case 'o':
        return O;
    case 'p':
        return P;
    case 'l':
        return L;
    case 'm':
        return M;
    default:
        break;
    }
    return NONE;
}

extern "C" IDisplay *create(void) {
    return new NcursesDisplay;
}

extern "C" void destroy(IDisplay *display) {
    delete display;
}
}  // namespace arc
