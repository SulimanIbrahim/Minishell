NAME = minishell
NAME_TEST = result
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
READLINE = -L/users/$(USER)/.brew/opt/readline/lib
LIBFT = ./Libft-42/libft.a

SRC = main.c\
	parsing.c\
	parsing_quotes.c\
  	check_redirections.c\
	replace_env_vars.c\
	cleaning_quotes.c\
	setting_redirections.c\
	tokenize_cmds.c\
	signal_handle.c\
	free.c\
	mini_split.c\
	execution.c\
	ft_builtins.c\
	shellvl.c\
	export.c\
	unset.c

SRC_TEST = test_driven.c\
	parsing.c\
	parsing_quotes.c\
  	check_redirections.c\
	replace_env_vars.c\
	cleaning_quotes.c\
	setting_redirections.c\
	tokenize_cmds.c\
	signal_handle.c\
	free.c

OBJ = $(SRC:%.c=%.o)

OBJ_TEST = $(SRC_TEST:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@make all -C ./Libft-42
	$(CC) $(CFLAGS) $(READLINE) $(OBJ) $(LIBFT) -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -l readline -o $(NAME)

test : $(NAME_TEST)

$(NAME_TEST) : $(OBJ_TEST)
	@make all -C ./Libft-42
	$(CC) $(CFLAGS) $(READLINE) $(OBJ_TEST) $(LIBFT) -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -l readline -o $(NAME_TEST) 
clean :
	@make clean -C ./Libft-42
	rm -rf $(OBJ) $(OBJ_TEST)

fclean : clean
	rm -rf $(NAME) $(NAME_TEST)
	@make fclean -C ./Libft-42

re : fclean all