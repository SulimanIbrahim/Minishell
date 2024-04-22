/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:04:29 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/22 23:08:55 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_red_fd(t_red_vars *red_fd)
{
	red_fd->tmp_in_fd = -1;
	red_fd->tmp_out_fd = -1;
	red_fd->input_fd = -1;
	red_fd->output_fd = -1;
	red_fd->input_type = -1;
	red_fd->output_type = -1;
}

void	set_reds(t_cmd *cmd, t_red_vars *red_fd)
{
	t_red		*p;

	p = cmd->redricts;
	while (p)
	{
		if (p->type == INPUT || p->type == HERDOC)
		{
			red_fd->input_type = p->type;
			if (p->type == INPUT)
				red_fd->input_fd = open(p->file_name, O_RDONLY);
			else if (p->input_herdoc_fd != -1)
				red_fd->input_fd = p->input_herdoc_fd;
		}
		else if (p->type == OUTPUT || p->type == APPEND)
		{
			if (p->type == APPEND)
				red_fd->output_fd = open(p->file_name, O_RDWR
						| O_APPEND | O_CREAT, 457);
			else
				red_fd->output_fd = open(p->file_name, O_RDWR
						| O_CREAT, 457);
			red_fd->output_type = p->type;
		}
		p = p->next_redricts;
	}
}

void	set_input_output(t_red_vars *red_fd)
{
	if (red_fd->input_fd != -1)
	{
		red_fd->tmp_in_fd = dup(STDIN_FILENO);
		dup2(red_fd->input_fd, STDIN_FILENO);
		close(red_fd->input_fd);
	}
	if (red_fd->output_fd != -1)
	{
		red_fd->tmp_out_fd = dup(STDOUT_FILENO);
		dup2(red_fd->output_fd, STDOUT_FILENO);
		close(red_fd->output_fd);
	}
}

void	close_input_output(t_red_vars *red_fd)
{
	if (red_fd->output_fd != -1)
	{
		close(red_fd->output_fd);
		dup2(red_fd->tmp_out_fd, STDOUT_FILENO);
		close(red_fd->tmp_out_fd);
	}
	if (red_fd->input_fd != -1)
	{
		close(red_fd->input_fd);
		dup2(red_fd->tmp_in_fd, STDIN_FILENO);
		close(red_fd->tmp_in_fd);
	}
}

void	execute_red(t_cmd *cmd, t_input *input, t_var *var)
{
	t_red_vars	red_fd;

	(void)var;
	init_red_fd(&red_fd);
	set_reds(cmd, &red_fd);
	set_input_output(&red_fd);
	if (ft_check_builtins(cmd, input))
	{
		close_input_output(&red_fd);
		close_herdoc_fd(cmd->redricts);
		unlink("tmp");
	}
	else if (var->cmd_path && var->flag == 0
		&& execve(var->cmd_path, cmd->cmd, input->env) == -1)
		ft_printf (2, "(%s) command not found !!!\n", cmd->cmd[0]);
	{
		close_input_output(&red_fd);
		close_herdoc_fd(cmd->redricts);
		unlink("tmp");
	}
}
