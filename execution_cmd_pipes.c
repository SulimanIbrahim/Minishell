/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:55:33 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/22 22:05:17 by ahibrahi         ###   ########.fr       */
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
		var->splitted = ft_split(ft_get_env("PATH", input->env), ':');
		if (!var->splitted || !var->splitted[0])
			return ((var->cmd_path = ft_strdup(cmd[var->i]->cmd[0]), true));
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
	var->flag = 0;
	if (cmd[var->i]->redricts)
		execute_red(cmd[var->i], input, var);
	else if (ft_check_builtins(cmd[var->i], input))
	{
		if (input->env)
			free_env(input->env);
		(free_all(cmd, input, var)), exit(EXIT_FAILURE);
	}
	else if (var->cmd_path
		&& execve(var->cmd_path, cmd[var->i]->cmd, input->env) == -1)
		ft_printf (2, "(%s) command not found !!!\n", cmd[var->i]->cmd[0]);
	if (input->env)
		free_env(input->env);
	(free_all(cmd, input, var)), exit(EXIT_FAILURE);
}

static bool	parent_dupping_fds(t_cmd **cmd, t_input *input, t_var *var)
{
	close_herdoc_fd(cmd[var->i]->redricts);
	if (close_prev_fd(var) == false)
		return (free_all(cmd, input, var), free(input->env), false);
	var->prev_fd = dup(var->fd[0]);
	if (var->prev_fd == -1)
	{
		if (input->env)
			free_env(input->env);
		(free_all(cmd, input, var));
		return (false);
	}
	close_fd(var);
	return (true);
}

static void	execute_pipes(t_cmd **cmd, t_input *input, t_var *var)
{
	var->i = -1;
	var->prev_fd = -1;
	while (++var->i < input->num_of_cmd && cmd[var->i])
	{
		if (cmd[var->i]->redricts)
			set_herdoc(cmd[var->i]->redricts, input);
		if (pipe(var->fd) == -1)
			return ;
		if (fork() == 0)
		{
			if (!child_dupping_fds(input, var))
			{
				if (input->env)
					free_env(input->env);
				(free_all(cmd, input, var)), exit(EXIT_FAILURE);
			}
			ft_check_exit(cmd, input, var, var->i);
			get_path(cmd, input, var);
			execute_execve(cmd, input, var);
		}
		else
			if (!parent_dupping_fds(cmd, input, var))
				break ;
	}
	close_prev_fd(var);
}

bool	execute(t_cmd **cmd, t_input *input, t_var *var)
{
	init_var(var);
	if (!*cmd)
		return (true);
	if (input->num_of_cmd == 1)
	{
		var->flag = 1;
		get_path(cmd, input, var);
		ft_check_exit(cmd, input, var, 0);
		if (cmd[0]->redricts)
			set_herdoc(cmd[0]->redricts, input);
		if (cmd[0]->redricts)
			execute_red(cmd[0], input, var);
		else if (ft_check_builtins(cmd[0], input))
			return (true);
		if (fork() == 0)
			execute_execve(cmd, input, var);
		else
			close_herdoc_fd(cmd[0]->redricts);
	}
	else
		execute_pipes(cmd, input, var);
	wait_process(input, var);
	return (true);
}
