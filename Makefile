SRC = ./src/main.cpp \
      ./src/Image.cpp

OBJ = $(SRC:.cpp=.o)
CFLAGS += -std=c++17 -Werror -Wextra -I./include
NAME = main.exe



$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ)


run	:
	./$(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


