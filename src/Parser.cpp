/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Parser
*/

#include<cstdlib>
#include <cstring>
#include <fstream>
#include "Parser.hpp"
#include "Error.hpp"

arc::Parser::Parser(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;

    if (file.is_open() == false)
        throw ParseError("Cannot open " + filename);
    lines = this->readLines(file);
    this->parseItems(lines);
    this->parseMap(lines);
}

std::vector<std::string> arc::Parser::readLines(std::ifstream &file)
{
    std::string line;
    std::vector<std::string> lines;

    while (getline(file, line))
        lines.push_back(line);
    return lines;
}

void arc::Parser::parseMap(std::vector<std::string> lines)
{
    std::vector<std::string> vectMap;
    size_t i = 0;
    char **map;

    if (lines.at(0).rfind("[maptiles]", 0) != 0)
        throw arc::ParseError("Missing [maptiles] label");
    lines.erase(lines.begin());
    lines.at(0).erase(0, lines.at(0).find('=') + 1);
    std::ifstream file(lines.at(0));
    if (file.is_open() == false)
        throw arc::ParseError("Cannot open " + lines.at(0));
    vectMap = this->readLines(file);
    map = (char **) malloc(sizeof(char *) * (vectMap.size() + 1));
    for (i = 0; i < vectMap.size(); i++) {
        //map[i] = (char *) malloc(sizeof(char) * vectMap.at(i).size());
        map[i] = strdup(vectMap.at(i).c_str());
    }
    map[i] = nullptr;
    this->_map = map;
}

void arc::Parser::parseItems(std::vector<std::string> &lines)
{
    if (lines.at(0).rfind("[items]", 0) != 0)
        throw ParseError("Missing [items] label");
    lines.erase(lines.begin());
    while (lines.size() > 0 && lines.at(0).rfind("[maptiles]", 0) != 0) {
        this->_items.push_back(this->createItem(lines.at(0)));
        lines.erase(lines.begin());
    }
}

arc::Parser::item arc::Parser::createItem(std::string line)
{
    std::vector<std::string> array;
    size_t pos = 0;
    std::string token;
    item item;

    array.push_back(line.substr(0, line.find('=')));
    line.erase(0, line.find('=') + 1);
    while ((pos = line.find(":")) != std::string::npos) {
        token = line.substr(0, pos);
        array.push_back(token);
        line.erase(0, pos + 1);
    }
    array.push_back(line);
    item.type = array.at(0);
    item.text = array.at(1).c_str()[0];
    item.graphic = array.at(2);
    item.mapRef = array.at(3).c_str()[0];
    return item;
}