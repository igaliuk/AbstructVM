NAME = abstract_vm

CC = clang++

FLAG = -Wall -Wextra -Werror -std=c++11

INC = ./headers

SRC = src/main.cpp \
	src/AbstractVM.cpp \
	src/Creator.cpp \
	src/Input.cpp \
	src/Lexer.cpp \
	src/Output.cpp \
	src/Parser.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "       Compiling abstract_vm....\n"
	@$(CC) $(FLAG) -o $@ $^
	@echo "                                  Done!\n"

%.o: %.cpp
	@$(CC) $(FLAG) -I$(INC) -c -o $@ $<

clean:
	@echo "\n       Deleting objects....\n"
	@rm -f $(OBJ)
	@echo "                                  Done!\n"

fclean: clean
	@echo "       Deleting objects and binary file....\n"
	@rm -f $(NAME)
	@echo "                                  Done!\n"

re: fclean all
