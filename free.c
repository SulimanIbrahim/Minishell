/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:46:24 by aken              #+#    #+#             */
/*   Updated: 2024/03/22 19:53:53 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_var(t_var	*var)
{
	var->i = 0;
	if (!var)
		return (0);
	if (var->temp)
		free(var->temp);
	if (var->path)
	{
		while (var->path[var->i])
			free(var->path[var->i++]);
		free(var->path);
	}
	return (0);
}

void	free_redirections(t_red	**redirection)
{
	t_red	*tmp;
	t_red	*p;

	if (!redirection)
		return ;
	p = *redirection;
	while (p)
	{
		tmp = p->next_redricts;
		free(p->file_name);
		free(p);
		p = tmp;
	}
	*redirection = NULL;
}

void	free_input(t_input *input)
{
	if (!input)
		return ;
	if (input->cmds)
		free (input->cmds);
}

void	free_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd_name)
		free (cmd->cmd_name);
	if (cmd->redricts)
		free_redirections(&(cmd->redricts));
	if (cmd->cmd)
	{
		while (cmd->cmd[i])
			free(cmd->cmd[i++]);
		free(cmd->cmd);
	}
	free(cmd);
}

void	free_all(t_cmd **cmd, t_input *input)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
			free_cmd(cmd[i++]);
		free(cmd);
	}
	free_input(input);
}
