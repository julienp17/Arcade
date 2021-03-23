##
## EPITECH PROJECT, 2021
## Arcade
## File description:
## Makefile
##

CC			=	g++

MAIN		=	$(addprefix $(SRC_D), main.cpp)
OBJ_M		=	$(MAIN:.cpp=.o)

SRC			=	$(addprefix $(SRC_D), $(SRC_F))
OBJ			=	$(SRC:.cpp=.o)
SRC_D		=	src/
SRC_F		=

SRC_UT		=	$(addprefix $(SRC_UT_D), $(SRC_UT_F))
OBJ_UT		=	$(SRC_UT:.cpp=.o)
SRC_UT_D	=	tests/
SRC_UT_F	=

INC			=	-I./inc \
				-I./inc/Core \
				-I./inc/Display \
				-I./inc/Games

WFLAGS		=	-W -Wall -Wextra -Werror

DBFLAGS		=	-g -g3 -ggdb

LDFLAGS		=

LDFLAGS_UT  =	-lgtest -lgtest_main -lpthread

CXXFLAGS	=	-std=c++14 $(WFLAGS) $(INC)

NAME		=	arcade

NAME_UT		=	unit_tests

all: $(NAME)

$(NAME): $(OBJ_M) $(OBJ)
	$(CC) $(CXXFLAGS) -o $(NAME) $(OBJ_M) $(OBJ) $(LDFLAGS)

debug: $(OBJ_M) $(OBJ)
	$(CC) $(CXXFLAGS) $(DBFLAGS) -o $(NAME) $(OBJ_M) $(OBJ)

doc: FORCE
	doxygen Doxyfile
FORCE:

tests_run: clean $(OBJ) $(OBJ_UT)
	$(CC) $(CXXFLAGS) -o $(NAME_UT) $(OBJ) $(OBJ_UT) $(LDFLAGS_UT)
	./$(NAME_UT)

coverage:
	gcovr -s --exclude tests/

coding-style:
	cpplint --recursive --filter=-legal/copyright --verbose=3 .

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_UT)
	rm -f *.gc*

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_UT)

re: fclean all

.PHONY: all debug doc tests_run coverage coding-style clean fclean re