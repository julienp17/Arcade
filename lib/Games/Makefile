##
## EPITECH PROJECT, 2021
## arcade [WSL: Ubuntu-20.04]
## File description:
## Makefile
##

all:
	make -C ./Nibbler/ all
	make -C ./Pacman/ all

coding-style:
	cpplint --recursive --filter=-legal/copyright --verbose=3 .

clean:
	make -C ./Nibbler/ clean
	make -C ./Pacman/ clean

fclean: clean
	make -C ./Nibbler/ fclean
	make -C ./Pacman/ fclean

re: fclean all

.PHONY: all debug doc tests_run coverage coding-style clean fclean re