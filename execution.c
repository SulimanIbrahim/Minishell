/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:17:41 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/20 20:12:16 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execute_cmd(t_cmd **cmd, t_input *input, t_var *var, int i)
{
	pid_t	id;
	int		fd;
	int		status;

	id = fork();
	if (id == 0)
	{
		init_var(var);
		if (cmd[i]->cmd[0][0] != '/')
		{
			var->path = ft_split(getenv("PATH"), ':');
			var->temp = ft_strjoin("/", cmd[i]->cmd[0]);
			while (var->path[var->i])
			{
				var->temp2 = ft_strjoin(var->path[var->i], var->temp);
				if (access(var->temp2, F_OK))
					;
				var->i++;
				free(var->temp2);
				var->temp2 = NULL;
			}
		}
		else
			var->temp2 = cmd[i]->cmd[0];
		if (!var->temp2 || execve(var->temp2, cmd[i]->cmd, input->env) == -1)
			printf("shell : command not found %s\n", cmd[i]->cmd[0]);
		free_all(cmd, input);
		free_var(var);
		exit (0);
	}
	wait(&status);
	return (true);
}

bool	execute(t_cmd **cmd, t_input *input, t_var *var)
{
	int		i;

	i = 0;
	if (input->num_of_cmd == 1)
	{
		if (!ft_check_builtins(cmd[i]->cmd_name, input->env))
			execute_cmd(cmd, input, var, i);
	}
	return (true);
}
