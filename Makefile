NAME = minishell
NAME_TEST = result
CFLAGS = -Wall -Wextra -Werror 
READLINE = -L/users/$(USER)/.brew/opt/readline/lib -lreadline
LIBFT = ./Libft-42/libft.a
SRC = main.c\
	parsing.c\
	parsing_quotes.c

SRC_TEST = test_driven.c\
			parsing_quotes.c\
			parsing.c
OBJ = $(SRC:%.c=%.o)

OBJ_TEST = $(SRC_TEST:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@make all -C ./Libft-42
	$(CC) $(CFLAGS) $(READLINE) $(LIBFT) $(OBJ) -o $(NAME)

test : $(NAME_TEST)

$(NAME_TEST) : $(OBJ_TEST)
	$(CC) $(CFLAGS) $(READLINE) $(LIBFT) $(OBJ_TEST) -o $(NAME_TEST) 
clean :
	@make clean -C ./Libft-42
	rm -rf $(OBJ) $(OBJ_TEST)

fclean : clean
	rm -rf $(NAME) $(NAME_TEST)
	@make fclean -C ./Libft-42

re : fclean all