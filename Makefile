NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3
READLINE = -I/Users/$(USER)/homebrew/opt/readline/include -L/Users/$(USER)/homebrew/opt/readline/lib
LIBFT = ./Libft-42/libft.a
PRINTF = ./ft_printf/printf.a

SRC =	main.c\
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
		execution_cmd_pipes.c\
		execution_cmd_pipes_utils.c\
		builtins_utils.c\
		builtins.c\
		shellvl.c\
		export.c\
		unset.c\
		echo.c\
		execute_red.c\
		get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c\
		execute_herdoc.c\
		expand_herdoc.c\
		get_env.c\
		utils.c
 
OBJ = $(SRC:%.c=%.o)

OBJ_TEST = $(SRC_TEST:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(PRINTF) $(LIBFT) $(READLINE) -o $(NAME) -l readline

$(PRINTF):
	@make all -C ./ft_printf

$(LIBFT):
	@make all -C ./Libft-42

clean :
	@make clean -C ./Libft-42
	@make clean -C ./ft_printf
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	@make fclean -C ./ft_printf
	@make fclean -C ./Libft-42

re : fclean all