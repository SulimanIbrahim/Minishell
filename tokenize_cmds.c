/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:48:25 by suibrahi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/16 06:52:33 by ahibrahi         ###   ########.fr       */
=======
/*   Updated: 2024/03/20 11:54:53 by ahibrahi         ###   ########.fr       */
>>>>>>> e71d4723a1539649c6a00d1d5adcb437bc40b619
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
extern int num_of_error;
=======
void	init_var(t_var *var)
{
	var->i = 0;
	var->j = 0;
	var->n = 0;
	var->c = 0;
	var->len = 0;
	var->closed = 0;
	var->temp = NULL;
}
>>>>>>> e71d4723a1539649c6a00d1d5adcb437bc40b619

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

bool	tokenize_cmds(t_input *input, t_cmd **cmd, t_var *var)
{
	var->len = -1;
	var->j = -1;
	var->n = -1;
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
				return (false);
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
	// try this to print each cmd and the redirections in it
<<<<<<< HEAD
	int i = 0;
	t_red *p;
	while (i < input->num_of_cmd)
	{
		var->c = -1;
		while (cmd[i]->cmd[++var->c])
			printf("%s num_oferror == %i\n", cmd[i]->cmd[var->c], num_of_error);
		p = cmd[i]->redricts;
		while (p)
		{
			printf("status == \"%i\"  file == \"%s\" \n", p->type, p->file_name);
			p = p->next_redricts;
		}
		printf("------- \n");
		i++;
	}
	return (true);
}
=======
	// int i = 0;
	// t_red *p;
	// while (i < input->num_of_cmd)
	// {
	// 	var->c = -1;
	// 	if (!cmd || !cmd[i])
	// 		return (true);
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
>>>>>>> e71d4723a1539649c6a00d1d5adcb437bc40b619
