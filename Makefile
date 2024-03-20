CC = cc
FLAGS = -Wall -Wextra -Werror

NAME = fractol
SRC = fractol.c utils/study_utils.c utils/color_utils.c utils/general_utils.c utils/hook_utils.c utils/drawing_utils.c utils/conversion_utils.c
OBJ = $(SRC:.c=.o)
INCLUDE = fractol.h

BONUS_NAME = fractol_bonus
BONUS_SRC = bonus/fractol_bonus.c bonus/utils/study_utils_bonus.c bonus/utils/color_utils_bonus.c bonus/utils/general_utils_bonus.c bonus/utils/hook_utils_bonus.c bonus/utils/drawing_utils_bonus.c bonus/utils/conversion_utils_bonus.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)
BONUS_INCLUDE = bonus/fractol_bonus.h

all: $(NAME)

$(NAME): $(OBJ)
	@($(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME))
	@echo "Mandatory executable linked successfully!"

$(OBJ): $(INCLUDE)

$(BONUS_OBJ): $(BONUS_SRC)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	@($(CC) $(BONUS_OBJ) -lmlx -framework OpenGL -framework AppKit -o $(BONUS_NAME))
	@echo "Bonus executable linked successfully!"

%.o: %.c
	@($(CC) $(FLAGS) -c $< -o $@)
	@echo "Compiled $<"

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)
	@echo "Cleaned object files for both mandatory and bonus"

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "Cleaned executable for both mandatory and bonus"

re: fclean all