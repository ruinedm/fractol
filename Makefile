CC = cc
FLAGS = 

NAME = fractol
SRC = fractol.c utils/maths_utils.c utils/color_utils.c utils/general_utils.c utils/str_utils.c
OBJ = $(SRC:.c=.o)
INCLUDE = fractol.h

all: $(NAME)

$(NAME): $(OBJ)
	@($(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME))
	@echo "Executable linked successfully!"

$(OBJ): $(INCLUDE)

%.o: %.c
	@($(CC) $(FLAGS) -c $< -o $@)
	@echo "Compiled $<"

clean:
	@rm -f $(OBJ)
	@echo "Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned executable"
