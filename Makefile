# Gregoire DUCHARME #
# 02/08/2016 #

SRC		= main.cpp \
		Maze.cpp \
		Edge.cpp \
		Parser.cpp \
		Cell.cpp \

OBJ		= $(SRC:.cpp=.o)

NAME		= mazer

CPP		= g++

ECHO		= echo -e

CPPFLAGS		= -std=c++14 -Wall -Wextra -pedantic

RM		= rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CPP) -o $(NAME) $(OBJ) $(LIB) $(CDFLAGS)
	@$(ECHO) "\E[33;5m\nCompilation done.\n\E[33;0m"

clean:
	$(RM) $(OBJ) $(NAME)
	@$(ECHO) "\E[33;5m\nClean done.\n\E[33;0m"

re:		clean all
