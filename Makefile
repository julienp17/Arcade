##
## EPITECH PROJECT, 2021
## Arcade
## File description:
## Makefile
##

all: core games graphicals

core:
	make -C ./lib/Core all

games:

graphicals:
	make -C ./lib/SDL2 all

doc: FORCE
	doxygen Doxyfile
FORCE:

coding-style:
	cpplint --recursive --filter=-legal/copyright --verbose=3 ./lib

clean:
	make -C ./lib/Core clean
	make -C ./lib/SDL2 clean

fclean: clean
	make -C ./lib/Core fclean
	make -C ./lib/SDL2 fclean

re: fclean all

.PHONY: all debug doc tests_run coverage coding-style clean fclean re