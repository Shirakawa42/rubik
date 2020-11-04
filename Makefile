.PHONY: make all clean fclean re

NAME = rubik

SRC_NAME = rubik.cpp Cube.cpp Parser.cpp Solver.cpp
OBJ_NAME = $(SRC_NAME:.cpp=.o)

SRC_PATH = src/
OBJ_PATH = obj/
INC = -I include/

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@clang++ $(INC) $(OBJ) -lm -o $(NAME)
	@echo "$(NAME) created"

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	@clang++ $(INC) -o $@ -c $<

clean:
	@rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "all is clean"

fclean: clean
	@rm -fv $(NAME)
	@echo "$(NAME) deleted"

re: fclean clean all