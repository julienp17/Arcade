/*
** EPITECH PROJECT, 202|
** arcade
** File description:
** testParser
*/

#include <gtest/gtest.h>
#include "Parser.hpp"
#include "Error.hpp"

TEST(Parser, parsed_items) {
    arc::Parser parser("./tests/parser/pacman_basic.ini");
    std::vector<arc::Parser::item> items = parser.getItems();

    ASSERT_EQ(items.at(0).type, std::string("wall"));
    ASSERT_EQ(items.at(0).token, '|');
    ASSERT_EQ(items.at(0).filepath, std::string("wall_file.png"));

    ASSERT_EQ(items.at(1).type, std::string("pacman"));
    ASSERT_EQ(items.at(1).token, 'P');
    ASSERT_EQ(items.at(1).filepath, std::string("pacman_file.png"));

    ASSERT_EQ(items.at(2).type, std::string("ghost"));
    ASSERT_EQ(items.at(2).token, 'M');
    ASSERT_EQ(items.at(2).filepath, std::string("ghost_file.png"));

    ASSERT_EQ(items.at(3).type, std::string("background"));
    ASSERT_EQ(items.at(3).token, '.');
    ASSERT_EQ(items.at(3).filepath, std::string("bg_file.png"));
}

TEST(Parser, parsed_map) {
    arc::Parser parser("./tests/parser/pacman_basic.ini");

    char **map = parser.getMap();
    ASSERT_STREQ(map[0], (char *)"|||||||||||||||||||||||||");
    ASSERT_STREQ(map[1], (char *)"|.......................|");
    ASSERT_STREQ(map[2], (char *)"|.|||||||||||||||||||||.|");
    ASSERT_STREQ(map[3], (char *)"|.|...................|.|");
    ASSERT_STREQ(map[4], (char *)"|......|.........|......|");
    ASSERT_STREQ(map[5], (char *)"|.|....|...MMM...|....|.|");
    ASSERT_STREQ(map[6], (char *)"|.||||||.........||||||.|");
    ASSERT_STREQ(map[7], (char *)"|......|.........|......|");
    ASSERT_STREQ(map[8], (char *)"|.|...................|.|");
    ASSERT_STREQ(map[9], (char *)"|.|||||||||||||||||||||.|");
    ASSERT_STREQ(map[10], (char *)"|...........P...........|");
    ASSERT_STREQ(map[11], (char *)"|||||||||||||||||||||||||");
}
