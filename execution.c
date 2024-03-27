/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:17:41 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/27 09:02:47 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_bin_file(t_cmd **cmd, t_var *var, int i)
{
	var->path = ft_split(getenv("PATH"), ':');
	var->temp = ft_strjoin("/", cmd[i]->cmd[0]);
	while (var->path[var->i])
	{
		var->temp2 = ft_strjoin(var->path[var->i], var->temp);
		if (access(var->temp2, F_OK) == 0)
			break ;
		var->i++;
		free(var->temp2);
		var->temp2 = NULL;
	}
}

bool	execute_cmd(t_cmd **cmd, t_input *input, t_var *var, int i)
{
	var->id = fork();
	if (var->id == 0)
	{
		init_var(var);
		if (!ft_strchr(cmd[i]->cmd[0], '/'))
		{
			check_bin_file(cmd, var, i);
			if (!var->temp2
				|| execve(var->temp2, cmd[i]->cmd, input->env) == -1)
				printf("shell : command not found %s\n", cmd[i]->cmd[0]);
			if (var->temp2)
				free(var->temp2);
		}
		else
		{
			var->temp2 = cmd[i]->cmd[0];
			if (!var->temp2
				|| execve(var->temp2, cmd[i]->cmd, input->env) == -1)
				printf("shell : command not found %s\n", cmd[i]->cmd[0]);
		}
		free_all(cmd, input);
		exit (free_var(var));
	}
	wait(&var->c);
	return (true);
}

bool	execute(t_cmd **cmd, t_input *input, t_var *var)
{
	int		i;

	i = 0;
	if (!cmd[0] || !cmd[0]->cmd || !cmd[0]->cmd[0])
		return (true);
	if (input->num_of_cmd == 1)
	{
		if (!ft_check_builtins(cmd[i], input))
			execute_cmd(cmd, input, var, i);
	}
	return (true);
}
