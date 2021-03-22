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
   Parser(const std::string &filename);
   virtual ~Parser(void) {}

 private:
   std::vector<std::string> readLines(std::ifstream &file);
   bool isFilenameCorrect(std::string filename);
   void parsePacman(std::vector<std::string> lines);
   void parseNibbler(std::vector<std::string> lines);
};

#endif /* !PARSER_HPP_ */
