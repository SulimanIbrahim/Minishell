/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:07:34 by aken              #+#    #+#             */
/*   Updated: 2024/04/22 22:07:41 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_redirection_2(char *cmd)
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
			return (HERDOC);
	}
	return (INPUT);
}

void	extracting_file_name(char *cmd, t_var *var)
{
	var->n = 0;
	var->j = 0;
	while (cmd[var->n] && cmd[var->n] != ' '
		&& cmd[var->n] != '<' && cmd[var->n] != '>')
	{
		if (cmd[var->n] && (cmd[var->n] == '\'' || cmd[var->n] == '"'))
			while (cmd[++var->n] && cmd[var->n] != '\'' && cmd[var->n] != '"')
				;
		else
			var->n++;
	}
	var->red->file_name = malloc(var->n + 1);
	var->n = 0;
	while (cmd[var->n] && cmd[var->n] != ' '
		&& cmd[var->n] != '<' && cmd[var->n] != '>')
	{
		if (cmd[var->n] && cmd[var->n] != '\'' && cmd[var->n] != '"')
			var->red->file_name[var->j++] = cmd[var->n++];
		else
		{
			var->k = cmd[var->n++];
			while (cmd[var->n] && cmd[var->n] != var->k)
				var->red->file_name[var->j++] = cmd[var->n++];
			if (cmd[var->n])
				var->n++;
		}
	}
	var->red->file_name[var->j] = '\0';
	var->i += var->n;
}

t_red	*alloc_redirection(void)
{
	t_red	*p;

	p = malloc(sizeof(t_red));
	p->input_herdoc_fd = -1;
	p->next_redricts = NULL;
	return (p);
}

void	add_redirection(t_red **redirection, t_red *var)
{
	t_red	*p;

	if (*redirection == NULL)
	{
		*redirection = var;
		return ;
	}
	p = *redirection;
	while (p->next_redricts)
		p = p->next_redricts;
	p->next_redricts = var;
}

void	set_redirection(t_cmd *cmd, t_var var)
{
	if (!ft_check_red(cmd->cmd_name)
		|| ft_check_redirections(cmd->cmd_name, &var))
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
			var.red->type = set_redirection_2(cmd->cmd_name + var.i);
			var.i += skip(cmd->cmd_name + var.i, cmd->cmd_name[var.i]);
			var.i += skip(cmd->cmd_name + var.i, ' ');
			extracting_file_name(cmd->cmd_name + var.i, &var);
			var.temp = malloc(var.closed + 1);
			ft_strlcpy(var.temp, cmd->cmd_name, var.closed + 1);
			var.cmd_tmp = cmd->cmd_name;
			cmd->cmd_name = ft_strjoin(var.temp, cmd->cmd_name + var.i);
			add_redirection(&(cmd->redricts), var.red);
			set_redirection(cmd, var);
			return (free(var.temp), free(var.cmd_tmp));
		}
	}
}
