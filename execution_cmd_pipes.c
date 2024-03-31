/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:55:33 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/31 06:51:49 by suibrahi         ###   ########.fr       */
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
		exit(1);
	}
}

static bool	execute_pipes(t_cmd **cmd, t_input *input, t_var *var)
{
	var->i = -1;
	var->prev_fd = STDIN_FILENO;
	while (++var->i < input->num_of_cmd)
	{
		if (pipe(var->fd) == -1) {
			perror("pipe ✅");
			return (false);
		}
		if (fork() == 0)
		{
			fprintf(stderr,"-----fd child-----\n");
			if (dup2(var->prev_fd, STDIN_FILENO) == -1)
				write(2,"true dup2 inside child STDIN ✅ \n", 35);
			if (close(var->prev_fd) == 0)
				fprintf(stderr, "true closing fd num(%d) prev_fd child\n", var->prev_fd);
			if ((var->i + 1) != input->num_of_cmd)			
				if (dup2(var->fd[1], STDOUT_FILENO) == -1)
					write(2,"true dup2 inside child STDOUT ✅\n",35);
			if (close(var->fd[0]) == 0)
				fprintf(stderr, "true closing fd num(%d) INPUT child\n", var->fd[0]);
			if (close(var->fd[1]) == 0)
				fprintf(stderr, "true closing fd num(%d) OUTPUT child\n", var->fd[1]);	
			get_path(cmd, var);
			execute_execve(cmd, input, var);
			exit(1);
		}
		else
		{
				// printf("-----fd parent-----\n");
			fprintf(stderr,"-----fd parent-----\n");
			var->prev_fd = var->fd[0];
			if (close(var->fd[1]) == 0)
				printf("true closing fd num(%d) OUTPUT parent\n", var->fd[1]);
		}
	}
	
	close(var->fd[1]);
	close(var->prev_fd);
	// var->c = -1;
	// while (++var->c < input->num_of_cmd)
	// 	close(var->prev_fd--);
	// 		// printf("true closing prev_fd num(%d)BARRRRAAA \n", var->prev_fd--);
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
			if (execve(var->cmd_path, cmd[0]->cmd, input->env) == -1)
				printf("(%s) command not found !!!\n", cmd[var->i]->cmd[0]);
			free_all(cmd, input, var);
			exit(1);
		}
	}
	else
		execute_pipes(cmd, input, var);
	var->c = -1;
	while (++var->c < input->num_of_cmd)
		wait(NULL);
	
	return (true);
}
