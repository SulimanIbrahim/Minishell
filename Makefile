NAME = minishell
NAME_TEST = result
CFLAGS = -Wall -Wextra -Werror
READLINE = -L/users/$(USER)/.brew/opt/readline/lib -lreadline
LIBFT = ./Libft-42/libft.a
SRC =	main.c\
		parsing.c\
		check_redirections.c\
		replace_env_vars.c

SRC_TEST =	test_driven.c\
			check_redirections.c\
			replace_env_vars.c\
			parsing.c\

OBJ = $(SRC:%.c=%.o)

OBJ_TEST = $(SRC_TEST:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@make all -C ./Libft-42
	$(CC) $(CFLAGS) $(READLINE) $(OBJ) $(LIBFT) -o $(NAME)

test : $(NAME_TEST)

$(NAME_TEST) : $(OBJ_TEST)
	@make all -C ./Libft-42
	$(CC) $(CFLAGS) $(READLINE) $(OBJ_TEST) $(LIBFT) -o $(NAME_TEST) 
clean :
	@make clean -C ./Libft-42
	rm -rf $(OBJ) $(OBJ_TEST)

fclean : clean
	rm -rf $(NAME) $(NAME_TEST)
	@make fclean -C ./Libft-42

re : fclean all