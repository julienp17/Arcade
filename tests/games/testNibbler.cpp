/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** testNibbler
*/

#include <gtest/gtest.h>
#include "Parser.hpp"
#include "Error.hpp"
#include "Nibbler.hpp"

TEST(Nibbler, nibbler_constructor) {
    arc::Parser parser("./tests/games/nibbler_basic.ini");
    arc::Nibbler nibbler(parser.getMap(), parser.getItems());

}
