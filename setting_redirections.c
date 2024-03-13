/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:07:34 by aken              #+#    #+#             */
/*   Updated: 2024/03/13 05:55:23 by aken             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_enm	set_redirection_2(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '>')
	{
		if (cmd[++i] && cmd[i] == '>')
			return (APPEND);
		else
			return (OUTPUT);
	}
	else if (cmd[i] == '<')
	{
		if (cmd[++i] && cmd[i] == '<')
		{
			if (cmd[++i] && cmd[i] == '>')
				return (HERSTR);
			else
				return (HERDOC);
		}
	}
	return (INPUT);
}

void	extracting_file_name(char *cmd, t_var *var)
{
	char	*file;

	var->n = 0;
	var->j = 0;
	while (cmd[var->n] && cmd[var->n] != ' ')
	{
		if (cmd[var->n] && cmd[var->n] != '\'' && cmd[var->n] != '"')
			var->j++;
		var->n++;
	}
	file = malloc(var->j + 1);
	var->n = 0;
	var->j = 0;
	while (cmd[var->n] && cmd[var->n] != ' ')
	{
		if (cmd[var->n] && cmd[var->n] != '\'' && cmd[var->n] != '"')
			file[var->j++] = cmd[var->n];
		var->n++;
	}
	file[var->j] = '\0';
	var->red->file_name = file;
	var->i += var->n;
}

t_red	*alloc_redirection(void)
{
	t_red	*p;

	p = malloc(sizeof(t_red) + 1);
	p->next_redricts = NULL;
	return (p);
}

void	add_redirection(t_red **redirection, t_red *var)
{
	t_red	*p;

	p = *redirection;
	if (!p)
	{
		*redirection = var;
		return ;
	}
	while (p->next_redricts)
		p = p->next_redricts;
	p->next_redricts = var;
}

void	set_redirection(t_cmd *cmd, t_var var)
{
	cmd->redricts = NULL;
	if (!ft_check_red(cmd->cmd_name))
		return ;
	var.i = -1;
	while (cmd->cmd_name[++var.i])
	{
		if (cmd->cmd_name[var.i] == '\'' || cmd->cmd_name[var.i] == '"')
			skip_quotes(cmd->cmd_name, &var.i, cmd->cmd_name[var.i]);
		if (cmd->cmd_name[var.i] == '>' || cmd->cmd_name[var.i] == '<')
		{
			var.closed = var.i;
			var.red = alloc_redirection();
			add_redirection(&(cmd->redricts), var.red);
			var.red->type = set_redirection_2(cmd->cmd_name + var.i);
			var.i += skip(cmd->cmd_name + var.i, cmd->cmd_name[var.i]);
			var.i += skip(cmd->cmd_name + var.i, ' ');
			extracting_file_name(cmd->cmd_name + var.i, &var);
			var.temp = malloc(var.closed + 2);
			ft_strlcpy(var.temp, cmd->cmd_name, var.closed + 1);
			cmd->cmd_name = ft_strjoin(var.temp, cmd->cmd_name + var.i);
			set_redirection(cmd, var);
			return ;
		}
	}
}
