/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:17:41 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/19 19:36:36 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(t_var *var)
{
	if (!var)
		return ;
	var->temp = NULL;
	var->temp2 = NULL;
	var->path = NULL;
}

bool	execute_cmd(t_cmd *cmd, t_input *input, t_var *var)
{
	pid_t	id;
	int		fd;
	int		status;

	var->i = 0;
	id = fork();
	if (id == 0)
	{
		init_var(var);
		if (cmd->cmd[0][0] != '/')
		{
			var->path = ft_split(getenv("PATH"), ':');
			var->temp = ft_strjoin("/", cmd->cmd[0]);
			while (var->path[var->i])
			{
				var->temp2 = ft_strjoin(var->path[var->i], var->temp);
				fd = open(var->temp2, O_RDONLY);
				if (fd > 0)
					break ;
				var->i++;
				free(var->temp2);
				var->temp2 = NULL;
			}
			close (fd);
		}
		else
			var->temp2 = cmd->cmd[0];
		if (execve(var->temp2, cmd->cmd, input->env) == -1)
			printf("shell : command not found %s\n", cmd->cmd[0]);
		free_var(var);
		exit (0);
	}
	wait(&status);
	return (true);
}

bool	execute(t_cmd **cmd, t_input *input, t_var *var)
{
	// int		i;

	// i = 0;
	if (input->num_of_cmd == 1)
		execute_cmd(cmd[0], input, var);
	return (true);
}
