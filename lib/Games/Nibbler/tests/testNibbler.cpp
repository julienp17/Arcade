/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** testNibbler
*/

#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include "Error.hpp"
#include "Nibbler.hpp"

TEST(Nibbler, loose) {
    arc::Parser parser("./tests/nibbler_basic.ini");
    arc::Nibbler nibbler(parser.getMap(), parser.getItems());

    nibbler.getMap();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    nibbler.getMap();
    ASSERT_EQ(nibbler.getGameState(), arc::IGame::LOOSE);
}

TEST(Nibbler, change_direction) {
    arc::Parser parser("./tests/nibbler_basic.ini");
    arc::Nibbler nibbler(parser.getMap(), parser.getItems());

    char **map = nibbler.getMap();

    for (int i = 0; map[i]; i++) {
        printf("%s\n", map[i]);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    map = nibbler.getMap();
    nibbler.execKey(arc::Input::UP);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    map = nibbler.getMap();
    nibbler.execKey(arc::Input::LEFT);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    map = nibbler.getMap();
    nibbler.execKey(arc::Input::DOWN);
    for (int i = 0; map[i]; i++) {
        printf("%s\n", map[i]);
    }
}
