/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:25:22 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/21 09:02:47 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool execute(t_cmd **cmd, t_input *input, t_var *var)
{
	var->id = 1;
	var->i = -1;
	var->j = 0;
	if (input->num_of_cmd == 1)
	{
		if (var->id == 0)
			exit(0);
		var->id = fork();
		if (var->id == 0)
		{
			var->len = ft_strlen(cmd[0]->cmd[0]);
			if (ft_strnstr(cmd[0]->cmd[0], "/bin/", var->len) == NULL)
				cmd[0]->cmd_path = ft_strjoin("/bin/", cmd[0]->cmd[0]);
			else
				cmd[0]->cmd_path = cmd[0]->cmd[0];
			if (execve(cmd[0]->cmd_path, cmd[0]->cmd, NULL) == -1)
				printf("command not found !!!\n");
			exit(0);
		}
	}
	else
	{
		while (++var->i < input->num_of_cmd)
		{
			if (var->id == 0)
				exit(0);
			var->id = fork();
			if (var->id == 0)
			{
				var->len = ft_strlen(cmd[var->i]->cmd[0]);
				if (ft_strnstr(cmd[var->i]->cmd[0], "/bin/", var->len) == NULL)
					cmd[var->i]->cmd_path = ft_strjoin("/bin/", cmd[0]->cmd[0]);
				else
					cmd[var->i]->cmd_path = cmd[var->i]->cmd[0];
				if (execve(cmd[var->i]->cmd_path, cmd[var->i]->cmd, NULL) == -1)
					printf("command not found !!!\n");
				exit(0);
			}
		}
	}
	wait(&var->status);
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
			clear_history();
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
				if (execute(cmd, &input, &var))
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
