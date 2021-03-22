/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** main
*/

#include <iostream>
#include "arcade.hpp"

int main(int ac, char **av) {
    (void)av;
    if (ac != 2) {
        std::cerr << USAGE << std::endl;
        return MY_EXIT_FAILURE;
    }
    return 0;
}
