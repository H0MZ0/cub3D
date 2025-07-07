CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -Lmlx -lmlx -lXext -lX11 -lm

NAME = cub3D

# Libft
LIBFT_DIR = LIBFT
LIBFT_A = $(LIBFT_DIR)/libft.a

# Sources and objects
SRC =	functions/tools1.c cleaner.c count_things.c ft_check.c is_what.c main.c \
		read_map.c clean_map.c print.c mlx.c
OBJ = $(SRC:.c=.o)

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBFT_A)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
