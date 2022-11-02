SRC = ./src/main.cpp \
      ./src/Image.cpp \
      ./src/Headers.cpp \
      ./src/Stb.cpp \
      ./src/MathFunc.cpp \
      ./src/Vector3.cpp \
      ./src/Vector2.cpp


OBJ = $(SRC:.cpp=.o)
CFLAGS += -std=c++17 -Wall -Werror -Wextra -lm -E -P -I./include
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
