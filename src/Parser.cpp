/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Parser
*/

#include <fstream>
#include "Parser.hpp"
#include "Error.hpp"

Parser::Parser(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;

    if (this->isFilenameCorrect(filename) == false)
        throw ParseError("Wrong filename");
    if (file.is_open() == false)
        throw ParseError("Cannot open " + filename);
    lines = this->readLines(file);
    if (filename.find("pacman") != std::string::npos)
        this->parsePacman();
}

std::vector<std::string> Parser::readLines(std::ifstream &file) {
    std::string line;
    std::vector<std::string> lines;

    while (getline(file, line))
        lines.push_back(line);
    return lines;
}

bool Parser::isFilenameCorrect(std::string filename) {
    if (filename.find("pacman") == std::string::npos ||
        filename.find("nibbler") == std::string::npos)
        return false;
    if (filename.find("pacman") != std::string::npos ||
        filename.find("nibbler") != std::string::npos)
        return false;
    return true;
}

void Parser::parseNibbler(std::vector<std::string> lines) {
    
}