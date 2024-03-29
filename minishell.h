/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 05:15:28 by aken              #+#    #+#             */
/*   Updated: 2024/03/21 08:38:55 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "Libft-42/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define PIPE 124
# define ANSI_COLOR_RED       "\x1b[31m"
# define ANSI_COLOR_GREEN     "\x1b[32m"
# define ANSI_COLOR_YELLOW    "\x1b[33m"
# define ANSI_COLOR_BLUE      "\x1b[34m"
# define ANSI_COLOR_MAGENTA   "\x1b[35m"
# define ANSI_COLOR_CYAN      "\x1b[36m"
# define ANSI_COLOR_RESET     "\x1b[0m"
# define ANSI_COLOR_BLACK     "\x1b[30m"
# define ANSI_COLOR_WHITE     "\x1b[37m"
# define ANSI_COLOR_BRIGHT_RED    "\x1b[91m"
# define ANSI_COLOR_BRIGHT_GREEN  "\x1b[92m"
# define ANSI_COLOR_BRIGHT_YELLOW "\x1b[93m"
# define ANSI_COLOR_BRIGHT_BLUE   "\x1b[94m"
# define ANSI_COLOR_BRIGHT_MAGENTA "\x1b[95m"
# define ANSI_COLOR_BRIGHT_CYAN   "\x1b[96m"
# define ANSI_COLOR_BG_RED        "\x1b[41m"
# define ANSI_COLOR_BG_GREEN      "\x1b[42m"
# define ANSI_COLOR_BG_YELLOW     "\x1b[43m"
# define ANSI_COLOR_BG_BLUE       "\x1b[44m"
# define ANSI_COLOR_BG_MAGENTA    "\x1b[45m"
# define ANSI_COLOR_BG_CYAN       "\x1b[46m"
# define ANSI_COLOR_BG_WHITE      "\x1b[47m"

typedef	enum
{
	INPUT,
	OUTPUT,
	APPEND,
	HERDOC,
	HERSTR,
}		t_enm;

typedef struct redirection
{
	int			type;
	char		*file_name;
	void		*next_redricts;
}		t_red;

typedef struct vars
{
	int		i;
	int		j;
	int		n;
	int		c;
	int		id;
	int		status;
	int		len;
	int		closed;
	int		*fd;
	char	*temp;
	char	*cmd_tmp;
	t_red	*red;
}		t_var;

typedef struct input
{
	char		*cmds;
	char		**env;
	int			num_of_cmd;
}	t_input;

typedef struct command
{
	char	*cmd_name;
	char	**cmd;
	char	*cmd_path;
	t_red	*redricts;
}		t_cmd;

int			skip(char *cmds, char c);
int			ft_check_redirections(t_input *input, t_var *vars);
bool		parsing(t_input *input);
bool		tokenize_cmds(t_input *input, t_cmd **cmds, t_var *var);
bool		clean_quotes(t_input *input, t_var *var);
bool		quote_parsing(char *line, t_var *var);
char		**dup_shell(char **env);
char		*ft_check_red(char *cmd_name);
char		*readline(const char *line);
void		rl_replace_line(const char *str, int line_num);
void		skip_quotes(char *input, int *i, int q_type);
void		ft_check_env(t_input *input, t_var *vars);
void		set_redirection(t_cmd *cmd, t_var var);
void		free_all(t_cmd **cmd, t_input *input);
void		signal_handler(int signum);
void		init_var(t_var *var);
void		free_input(t_input *input);
void		add_shlvl(char **env);
char		**mini_split(char *s, char c);

#endif
