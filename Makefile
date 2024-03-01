NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
READLINE = -L/users/$(USER)/.brew/opt/readline/lib -lreadline
LIBFT = ./Libft-42/libft.a
SRC = main.c\
	parsing.c

OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@make all -C ./Libft-42
	$(CC) $(CFLAGS) $(READLINE) $(LIBFT) $(OBJ) -o $(NAME)

clean :
	@make clean -C ./Libft-42
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	@make fclean -C ./Libft-42

re : fclean all