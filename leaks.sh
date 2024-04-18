valgrind --suppressions=../valgrind_readline_leaks_ignore.txt --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes .././minishell
