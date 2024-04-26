/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:48:25 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/16 16:07:58 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(t_var *var)
{
	var->i = 0;
	var->j = 0;
	var->n = 0;
	var->c = 0;
	var->flag = 0;
	var->len = 0;
	var->closed = 0;
	var->temp = NULL;
	var->cmd_path = NULL;
	var->cmd_tmp = NULL;
	var->splitted = NULL;
}

static	void	init_token_var(t_var *var)
{
	var->i = -1;
	var->j = -1;
	var->n = -1;
	var->flag = 1;
	var->len = -1;
}

static bool	find_pipe(t_input *input, int *len)
{
	if (input->cmds[*(len)] == DOUBLE_QUOTE)
		skip_quotes(input->cmds, len, DOUBLE_QUOTE);
	if (input->cmds[*(len)] == SINGLE_QUOTE)
		skip_quotes(input->cmds, len, SINGLE_QUOTE);
	if (input->cmds[*(len)] == PIPE)
		return (true);
	return (false);
}

void	tokenize_cmds(t_input *input, t_cmd **cmd, t_var *var)
{
	init_token_var(var);
	while (input->cmds[++var->len])
	{
		find_pipe(input, &var->len);
		if (!input->cmds[var->len])
			break ;
		if (input->cmds[var->len + 1] == '\0' || input->cmds[var->len] == PIPE)
		{
			if (input->cmds[var->len + 1] == '\0')
				var->len++;
			var->i = -1;
			cmd[++var->j] = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
			cmd[var->j]->cmd_name = (char *)malloc(var->len + 1);
			if (!cmd[var->j] || !cmd[var->j]->cmd_name)
				return ;
			while (var->n < var->len)
				cmd[var->j]->cmd_name[++var->i] = input->cmds[++var->n];
			cmd[var->j]->cmd_name[var->i] = '\0';
			cmd[var->j]->redricts = NULL;
			set_redirection(cmd[var->j], (*var));
			cmd[var->j]->cmd = mini_split(cmd[var->j]->cmd_name, ' ');
		}
		if (!input->cmds[var->len])
			break ;
	}
}
	// int 	i = 0;
	// t_red	*p;
	// while (i < input->num_of_cmd)
	// {
	// 	var->c = -1;
	// 	if (!cmd || !cmd[i])
	// 		return ;
	// 	while (cmd[i]->cmd[++var->c])
	// 		printf("%s\n", cmd[i]->cmd[var->c]);
	// 	p = cmd[i]->redricts;
	// 	while (p)
	// 	{
	// 		printf("status == \"%i\"  file == \"%s\" \n", p->type, p->file_name);
	// 		p = p->next_redricts;
	// 	}
	// 	printf("------- \n");
	// 	i++;
	// }
	// try this to print each cmd and the redirections in it