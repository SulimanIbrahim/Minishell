/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:55:33 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/18 05:56:13 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_path(t_cmd **cmd, t_input *input, t_var *var)
{
	var->j = -1;
	if (!cmd[var->i]->cmd || !cmd[var->i]->cmd[0])
		return (true);
	if (ft_strchr(cmd[var->i]->cmd[0], '/') == NULL)
	{
		var->splitted = ft_split(ft_get_env_path(input->env), ':');
		if (!var->splitted)
			return (false);
		while (var->splitted[++var->j])
		{
			var->temp = ft_strjoin(var->splitted[var->j], "/");
			var->cmd_path = ft_strjoin(var->temp, cmd[var->i]->cmd[0]);
			if (access(var->cmd_path, F_OK) == 0)
				return (free(var->temp), true);
			if (var->splitted[var->j + 1] == NULL)
				return (free(var->temp), false);
			free(var->temp);
			free(var->cmd_path);
		}
	}
	else
		var->cmd_path = ft_strdup(cmd[var->i]->cmd[0]);
	return (true);
}

static void	execute_execve(t_cmd **cmd, t_input *input, t_var *var)
{
	if (!get_path(cmd, input, var))
	{
		printf("(%s) command not found !!!\n", cmd[var->i]->cmd[0]);
		if (var->cmd_path)
			free(var->cmd_path);
		if (input->env)
			free_env(input->env);
		free_all(cmd, input, var);
		close_all(var);
		exit(0);
	}
	if (cmd[var->i]->redricts)
		execute_red(cmd[var->i], input, var);
	else if (var->cmd_path
		&& execve(var->cmd_path, cmd[var->i]->cmd, input->env) == -1)
		printf("(%s) command not found !!!\n", cmd[var->i]->cmd[0]);
	if (var->cmd_path)
		free(var->cmd_path);
	if (input->env)
		free_env(input->env);
	free_all(cmd, input, var);
	close_all(var);
	exit(1);
}

static void	execute_pipes(t_cmd **cmd, t_input *input, t_var *var)
{
	var->i = -1;
	var->prev_fd = STDIN_FILENO;
	var->flag = 0;
	while (++var->i < input->num_of_cmd && cmd[var->i])
	{
		ft_check_exit(cmd, input, var, var->i);
		if (cmd[var->i]->redricts)
			set_herdoc(cmd[var->i]->redricts);
		if (!ft_check_builtins(cmd[var->i], input))
		{
			if (pipe(var->fd) == -1)
				return ;
			if (fork() == 0)
			{
				dup2(var->prev_fd, STDIN_FILENO);
				close(var->prev_fd);
				if ((var->i + 1) != input->num_of_cmd)
					dup2(var->fd[1], STDOUT_FILENO);
				close_fd(var);
				execute_execve(cmd, input, var);
			}
			else
			{
				close_herdoc_fd(cmd[var->i]->redricts);
				var->prev_fd = dup(var->fd[0]);
				close_fd(var);
				var->flag++;
			}
		}
	}
	if (var->flag != 0)
		close_all(var);
}

bool	execute(t_cmd **cmd, t_input *input, t_var *var)
{
	init_var(var);
	if (!*cmd)
		return (true);
	if (input->num_of_cmd == 1)
	{
		ft_check_exit(cmd, input, var, 0);
		if (cmd[0]->redricts)
			set_herdoc(cmd[0]->redricts);
		if (ft_check_builtins(cmd[0], input))
			return (true);
		else if (fork() == 0)
		{
			execute_execve(cmd, input, var);
		}
		else
			close_herdoc_fd(cmd[0]->redricts);
	}
	else
		execute_pipes(cmd, input, var);
	var->c = -1;
	while (++var->c < input->num_of_cmd)
		wait(NULL);
	return (true);
}
