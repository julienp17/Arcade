##
## EPITECH PROJECT, 2021
## arcade [WSL: Ubuntu-20.04]
## File description:
## Makefile
##

all:
	make -C ./SDL2/ all
	make -C ./Ncurses/ all

clean:
	make -C ./SDL2/ clean
	make -C ./Ncurses/ clean

fclean: clean
	make -C ./SDL2/ fclean
	make -C ./Ncurses/ fclean

re: fclean all

.PHONY: all debug doc tests_run coverage coding-style clean fclean re