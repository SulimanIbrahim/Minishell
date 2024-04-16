/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:04:29 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/16 14:13:42 by ahibrahi         ###   ########.fr       */
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
	red_fd->key = NULL;
}

void	close_herdoc_fd(t_red *p)
{
	while (p)
	{
		if (p->input_herdoc_fd != -1)
		{
			printf("%d\n", p->input_herdoc_fd);
			close(p->input_herdoc_fd);
		}
		p = p->next_redricts;
	}
}

void	set_herdoc(t_red *p)
{
	char	*tmp;

	while (p)
	{
		if (p->type == HERDOC)
		{
			unlink("tmp");
			p->input_herdoc_fd = open("tmp", O_CREAT | O_RDWR, 0777);
			ft_putstr_fd("> ", STDOUT_FILENO);
			tmp = get_next_line(STDIN_FILENO);
			while (tmp && !(ft_strlen(p->file_name) == ft_strlen(tmp) - 1
					&& !ft_strncmp(p->file_name, tmp, ft_strlen(p->file_name))))
			{
				ft_putstr_fd("> ", STDOUT_FILENO);
				ft_putstr_fd(tmp, p->input_herdoc_fd);
				free(tmp);
				tmp = get_next_line(STDIN_FILENO);
			}
			if (tmp)
				free(tmp);
			close(p->input_herdoc_fd);
			p->input_herdoc_fd = open("tmp", O_RDONLY | O_CREAT, 0777);
		}
		p = p->next_redricts;
	}
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
						| O_APPEND | O_CREAT, 0777);
			else
				red_fd->output_fd = open(p->file_name, O_RDWR
						| O_CREAT, 0777);
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

void	execute_red(t_cmd *cmd, t_input *input, t_var *var)
{
	t_red_vars	red_fd;

	init_red_fd(&red_fd);
	set_reds(cmd, &red_fd);
	set_input_output(&red_fd);
	if (var->cmd_path && execve(var->cmd_path, cmd->cmd, input->env) == -1)
		printf("(%s) command not found !!!\n", cmd->cmd[0]);
	if (red_fd.output_fd != -1)
	{
		close(red_fd.output_fd);
		dup2(red_fd.tmp_out_fd, STDOUT_FILENO);
		close(red_fd.tmp_out_fd);
	}
	if (red_fd.input_fd != -1)
	{
		close(red_fd.input_fd);
		dup2(red_fd.tmp_in_fd, STDIN_FILENO);
		close(red_fd.tmp_in_fd);
	}
	close_herdoc_fd(cmd->redricts);
	unlink("tmp");
}
