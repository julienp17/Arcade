/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** NcursesDisplay
*/

#include <string.h>
#include <iostream>
#include "NcursesDisplay.hpp"
#include "Error.hpp"

namespace arc {
void NcursesDisplay::createWindow(void) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    clear();
}

void NcursesDisplay::destroyWindow(void) {
    endwin();
}

void NcursesDisplay::draw(map_t map) const {
    for (size_t i = 0 ; map[i] ; i++)
        addstr(map[i]);
    refresh();
}

void NcursesDisplay::drawText(int x, int y, const char *text) {
    if (x < 0 || x > 100 || y < 0 || y > 100)
        throw DisplayError("x or y percentage not in range [0, 100]");
    x = x * getmaxx(stdscr) / 100;
    y = y * getmaxy(stdscr) / 100;
    mvaddstr(y, x - (strlen(text) / 2), text);
    refresh();
}

void NcursesDisplay::clear(void) {
    using ::clear;  // use ncurse's clear function instead of member function
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
