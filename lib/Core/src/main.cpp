/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** main
*/

#include <iostream>
#include "Core.hpp"

int main(int ac, char **av) {
    arc::Core core;

    if (ac != 2) {
        std::cerr << USAGE << std::endl;
        return MY_EXIT_FAILURE;
    }
    (void)av;
    return 0;
}
