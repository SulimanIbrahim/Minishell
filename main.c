/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:25:22 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/16 05:49:51 by aken             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool execute(t_cmd *cmd, t_input *input, char **env)
{
	int i = 0;
	int id = 1;
	int status;
	char *command;

	env = NULL;
	i = -1;
	while (++i < input->num_of_cmd)
	{
		if (id == 0)
			exit(0);
		id = fork();
		if (id == 0)
		{
			command = ft_strjoin("/bin/", cmd[i].cmd_name);
			if (execve(command, &cmd[i].cmd_name, env) == -1)
				printf("shell : command not found !!!\n");
			exit(0);
		}
	}
	wait(&status);
	return (true);
}

int main (int ac, char **av, char **env)
{
	t_input	input;
	t_var	var;
	t_cmd	**cmd;

	(void)av;
	(void)ac;
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		input.num_of_cmd = 1;
		input.cmds = readline("\x1b[94mMinishell >> \x1b[0m");
		// input.cmds = ft_strdup("ls >$ n $PATH >k	$p");
		input.env = env;
		if (!input.cmds)
		{
			free_all(NULL, &input);
			exit(1);
		}
		add_history(input.cmds);
		if (parsing(&input))
		{
			cmd = (t_cmd **)ft_calloc(input.num_of_cmd, sizeof(t_cmd));
			cmd[input.num_of_cmd] = NULL;
			tokenize_cmds(&input, cmd, &var);
			if (cmd)
			{
				// if (execute(cmd, &input, env))
				free_all(cmd, &input);
					// exit(0);
			}
			else
				continue ;
		}
		continue ;
	}
	return (0);
}
