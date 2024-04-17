/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 05:15:28 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/17 07:19:54 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "Libft-42/libft.h"
# include "get_next_line/get_next_line.h"
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

typedef enum
{
	INPUT,
	OUTPUT,
	APPEND,
	HERDOC,
}		t_enm;

typedef struct redirection
{
	int			type;
	int			input_herdoc_fd;
	char		*file_name;
	void		*next_redricts;
}		t_red;

typedef struct redirection_vars
{
	int			input_fd;
	int			input_type;
	int			output_fd;
	int			output_type;
	int			tmp_in_fd;
	int			tmp_out_fd;
}			t_red_vars;

typedef struct vars
{
	int		i;
	int		j;
	int		n;
	int		c;
	int		id;
	char	k;
	int		status;
	int		len;
	int		closed;
	int		fdnum;
	int		fd[2];
	int		prev_fd;
	int		flag;
	bool	nflag;
	char	**splitted;
	char	*temp;
	char	*cmd_path;
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
	char		*cmd_name;
	char		**cmd;
	char		*cmd_path;
	t_red		*redricts;
	t_red_vars	red_vars;
}		t_cmd;

int			skip(char *cmds, char c);
int			ft_check_redirections(char *cmd_name, t_var *vars);
bool		ft_check_builtins(t_cmd *cmd, t_input *input);
bool		parsing(t_input *input);
void		tokenize_cmds(t_input *input, t_cmd **cmds, t_var *var);
bool		clean_quotes(t_input *input, t_var *var);
bool		quote_parsing(char *line, t_var *var);
char		**dup_shell(char **env);
char		*ft_check_red(char *cmd_name);
char		**mini_split(char *s, char c);
char		*readline(const char *line);
void		rl_replace_line(const char *str, int line_num);
void		skip_quotes(char *input, int *i, int q_type);
void		ft_check_env(t_input *input, t_var *vars);
void		set_redirection(t_cmd *cmd, t_var var);
void		free_all(t_cmd **cmd, t_input *input, t_var *var);
void		signal_handler(int signum);
void		init_var(t_var *var);
void		free_input(t_input *input);
void		add_shlvl(char **env);
bool		execute(t_cmd **cmd, t_input *input, t_var *var);
void		free_vars(t_var *var);
void		free_splitted(t_var *var);
void		wait_process(t_input *input, t_var *var);
void		close_fd(t_var *var);
void		init_all(t_var *var);
void		free_env(char **env);
void		free_cmd(t_cmd *cmd);
int			env_len(char **env);
void		export(t_cmd *cmd, t_input *input);
void		unset(t_cmd *cmd, t_input *input);
int			cd(t_cmd *cmd);
int			pwd(void);
int			ft_env(char **env);
void		free_split(char **split);
int			ft_exit(t_cmd **cmd, t_input *input, t_var *var);
void		ft_check_exit(t_cmd **cmd, t_input *input, t_var *var, int n);
int			str_is_digit(char *str);
char		**mini_split(char *s, char c);
void		execute_red(t_cmd *cmd, t_input *input, t_var *var);
void		close_all(t_var *var);
void		set_herdoc(t_red *p, t_input *input);
bool		echo(char **cmd);
void		close_herdoc_fd(t_red *p);
char		*expand_herdoc(char *line, t_input *input);
char		*env_srch(char *cmd);

#endif
