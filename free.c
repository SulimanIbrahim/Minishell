/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:46:24 by aken              #+#    #+#             */
/*   Updated: 2024/03/26 05:10:24 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_vars(t_var *var)
{
	if (var->cmd_path)
		free (var->cmd_path);
	if (var->temp)
		free (var->temp);
	if (var->cmd_tmp)
		free (var->cmd_tmp);
	if (var->splitted)
	{
		var->i = -1;
		while (var->splitted[var->i])
			free(var->splitted[var->i]);
		free(var->splitted);
	}
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

void	free_all(t_cmd **cmd, t_input *input, t_var *var)
{
	int	i;
	(void)var;
	i = 0;
	if (cmd)
	{
		while (cmd[i])
			free_cmd(cmd[i++]);
		free(cmd);
	}
	free_input(input);
	// free_vars(var);
}
