/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Parser
*/

#ifndef INC_PARSER_HPP_
#define INC_PARSER_HPP_

#include <string>
#include <vector>

namespace arc {
class Parser {
 public:
    struct item {
        std::string type;
        char sym;
        std::string path;
    };
    explicit Parser(const std::string &filename);
    virtual ~Parser(void) {}

    inline std::vector<item> getItems(void) const { return _items;}
    inline char **getMap(void) const { return _map;}

 private:
    std::vector<std::string> readLines(std::ifstream &file);
    bool isFilenameCorrect(std::string filename);

    void parseMap(std::vector<std::string> lines);
    void parseItems(std::vector<std::string> &lines);
    item createItem(std::string line);

    std::vector<item> _items;
    char **_map;
};
}  // namespace arc
#endif  // INC_PARSER_HPP_
