/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Parser
*/

#include<cstdlib>
#include <fstream>
#include "Parser.hpp"
#include "Error.hpp"

Parser::Parser(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;

    if (file.is_open() == false)
        throw ParseError("Cannot open " + filename);
    lines = this->readLines(file);
    this->parseItems(lines);
    this->parseMap(lines);
}

std::vector<std::string> Parser::readLines(std::ifstream &file) {
    std::string line;
    std::vector<std::string> lines;

    while (getline(file, line))
        lines.push_back(line);
    return lines;
}

void Parser::parseMap(std::vector<std::string> lines) {
    std::vector<std::string> vectMap;

    if (lines.at(0).rfind("[maptiles]", 0) != 0)
        throw ParseError("Missing [maptiles] label");
    lines.erase(lines.begin());
    lines.at(0).erase(0, lines.at(0).find('='));
    std::ifstream file(lines.at(0));
    if (file.is_open() == false)
        throw ParseError("Cannot open map");
    vectMap = this->readLines(file);
    this->_map = new char *[vectMap.size()];
    for (size_t i = 0; i < vectMap.size(); i++) {
        this->_map[i] = new char [vectMap.at(i).size()];
        this->_map[i] = vectMap.at(i).c_str();
    }
}

    void Parser::parseItems(std::vector<std::string> &lines)
{
    if (lines.at(0).rfind("[items]", 0) != 0)
        throw ParseError("Missing [items] label");
    lines.erase(lines.begin());
    while (lines.size() > 0 && lines.at(0).rfind("[maptiles]", 0) != 0) {
        this->_items.push_back(this->createItem(lines.at(0)));
        lines.erase(lines.begin());
    }
}

Parser::item Parser::createItem(std::string line) {
    std::vector<std::string> array;
    size_t pos = 0;
    std::string token;
    item item;

    line.erase(0, line.find('='));
    while ((pos = line.find(":")) != std::string::npos) {
        token = line.substr(0, pos);
        array.push_back(token);
        line.erase(0, pos + 1);
    }
    array.push_back(line);
    item.type = array.at(0);
    item.graphic = array.at(1);
    item.text = array.at(2).c_str()[0];
    return item;
}