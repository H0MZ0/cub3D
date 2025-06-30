CC = cc
# CFLAGS = -Wall -Wextra -Werror

NAME = cub3D

# Libft
LIBFT_DIR = LIBFT
LIBFT_A = $(LIBFT_DIR)/libft.a

# Sources and objects
SRC = main.c tools1.c
OBJ = $(SRC:.c=.o)

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_A)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
