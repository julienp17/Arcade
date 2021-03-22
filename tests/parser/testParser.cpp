/*
** EPITECH PROJECT, 2021
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
    ASSERT_EQ(items.at(0).text, '|');
    ASSERT_EQ(items.at(0).graphic, std::string("wall_file.png"));
    ASSERT_EQ(items.at(0).mapRef, '1');

    ASSERT_EQ(items.at(1).type, std::string("pacman"));
    ASSERT_EQ(items.at(1).text, 'P');
    ASSERT_EQ(items.at(1).graphic, std::string("pacman_file.png"));
    ASSERT_EQ(items.at(1).mapRef, '2');

    ASSERT_EQ(items.at(2).type, std::string("ghost"));
    ASSERT_EQ(items.at(2).text, 'M');
    ASSERT_EQ(items.at(2).graphic, std::string("ghost_file.png"));
    ASSERT_EQ(items.at(2).mapRef, '3');

    ASSERT_EQ(items.at(3).type, std::string("background"));
    ASSERT_EQ(items.at(3).text, '.');
    ASSERT_EQ(items.at(3).graphic, std::string("bg_file.png"));
    ASSERT_EQ(items.at(3).mapRef, '4');
}

TEST(Parser, parsed_map) {
    arc::Parser parser("./tests/parser/pacman_basic.ini");

    char **map = parser.getMap();
    ASSERT_STREQ(map[0], (char *)"1111111111111111111111111");
    ASSERT_STREQ(map[1], (char *)"1444444444444444444444441");
    ASSERT_STREQ(map[2], (char *)"1411111111111111111111141");
    ASSERT_STREQ(map[3], (char *)"1414444444444444444444141");
    ASSERT_STREQ(map[4], (char *)"1444444144444444414444441");
    ASSERT_STREQ(map[5], (char *)"1414444144433344414444141");
    ASSERT_STREQ(map[6], (char *)"1411111144444444411111141");
    ASSERT_STREQ(map[7], (char *)"1444444144444444414444441");
    ASSERT_STREQ(map[8], (char *)"1414444444444444444444141");
    ASSERT_STREQ(map[9], (char *)"1411111111111111111111141");
    ASSERT_STREQ(map[10], (char *)"1444444444442444444444441");
    ASSERT_STREQ(map[11], (char *)"1111111111111111111111111");
}