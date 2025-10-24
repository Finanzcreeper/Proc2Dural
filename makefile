CXX = g++
CXXFLAGS = -g3 -Wall -Wextra -Werror

SRC = tile.cpp main.cpp random.cpp connection_rules.cpp map.cpp
OBJ = $(SRC:.cpp=.o)

NAME = gen

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all