/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:55:33 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/29 04:46:55 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_path(t_cmd **cmd, t_var *var)
{
	var->j = -1;
	if (ft_strchr(cmd[var->i]->cmd[0], '/') == NULL)
	{
		var->splitted = ft_split(getenv("PATH"), ':');
		while (var->splitted[++var->j])
		{
			var->temp = ft_strjoin(var->splitted[var->j], "/");
			var->cmd_path = ft_strjoin(var->temp, cmd[var->i]->cmd[0]);
			if (access(var->cmd_path, F_OK) == 0)
				break ;
			if (var->splitted[var->j + 1] == NULL)
				break ;
			free(var->temp);
			free(var->cmd_path);
		}
	}
	else
	{
		if (access(cmd[var->i]->cmd[0], F_OK) == 0)
			return (true);
		else
			var->cmd_path = cmd[var->i]->cmd[0];
	}
	return (true);
}

static void	execute_execve(t_cmd **cmd, t_input *input, t_var *var)
{
	if (execve(var->cmd_path, cmd[var->i]->cmd, input->env) == -1)
	{
		printf("(%s) command not found !!!\n", cmd[var->i]->cmd[0]);
		free_all(cmd, input, var);
		exit(0);
	}
}

static bool	execute_pipes(t_cmd **cmd, t_input *input, t_var *var)
{
	var->i = -1;
	var->prev_fd = STDIN_FILENO;
	while (++var->i < input->num_of_cmd)
	{
		pipe(var->fd);
		if (fork() == 0)
		{
			dup2(var->prev_fd, STDIN_FILENO);
			close(var->prev_fd);
			if ((var->i + 1) != input->num_of_cmd)
				dup2(var->fd[1], STDOUT_FILENO);
			close_fd(var);
			get_path(cmd, var);
			execute_execve(cmd, input, var);
		}
		else
		{
			var->prev_fd = dup(var->fd[0]);
			close_fd(var);
		}
	}
	close(var->prev_fd);
	close_fd(var);
	return (true);
}

bool	execute(t_cmd **cmd, t_input *input, t_var *var)
{
	var->i = -1;
	init_var(var);
	if (!*cmd)
		return (true);
	if (input->num_of_cmd == 1)
	{
		if (fork() == 0)
		{
			get_path(cmd, var);
			printf("cmd[0]->cmd[0] = <%s>\n", cmd[0]->cmd[0]);
			printf("cmd[0]->cmd[1] = <%s>\n", cmd[0]->cmd[1]);
			if (execve(var->cmd_path, cmd[0]->cmd, input->env) == -1)
				printf("(%s) command not found !!!\n", cmd[var->i]->cmd[0]);
			free_all(cmd, input, var);
			exit(0);
		}
	}
	else
		execute_pipes(cmd, input, var);
	var->c = 0;
	while (var->c < input->num_of_cmd)
	{
		wait(NULL);
		var->c++;
	}
	return (true);
}
