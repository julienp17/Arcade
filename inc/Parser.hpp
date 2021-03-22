/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include <vector>

class Parser {
 public:
    struct item {
        std::string type;
        std::string graphic;
        char text;
    };
    Parser(const std::string &filename);
    virtual ~Parser(void) {}

 private:
    std::vector<std::string> readLines(std::ifstream &file);
    bool isFilenameCorrect(std::string filename);

    void parseMap(std::vector<std::string> lines);
    void parseItems(std::vector<std::string> &lines);
    item createItem(std::string line);

    inline std::vector<item> getItems(void) const { return _items;};
    inline char const **getMap(void) const { return _map;};

    std::vector<item> _items;
    char const **_map;
};

#endif /* !PARSER_HPP_ */
