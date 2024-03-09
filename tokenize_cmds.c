/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:48:25 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/09 07:57:25 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	find_pipe(t_input *input, int *len)
{
	if (input->cmds[*(len)] == DOUBLE_QUOTE)
		skip_quotes(input, len, DOUBLE_QUOTE);
	if (input->cmds[*(len)] == SINGLE_QUOTE)
		skip_quotes(input, len, SINGLE_QUOTE);
	if (input->cmds[*(len)] == PIPE)
		return (true);
	return (false);
}

bool	tokenize_cmds(t_input *input, t_cmd *cmd, t_var *var)
{
	var->len = -1;
	var->j = -1;
	var->n = -1;
	while (input->cmds[++var->len])
	{
		find_pipe(input, &var->len);
		if (input->cmds[var->len + 1] == '\0' || input->cmds[var->len] == PIPE)
		{
			if (input->cmds[var->len + 1] == '\0')
				var->len++;
			var->i = -1;
			cmd[++var->j].cmd_name = (char *)malloc((var->len) * sizeof(char));
			if (!cmd[var->j].cmd_name)
				return (false);
			while (var->n < var->len)
				cmd[var->j].cmd_name[++var->i] = input->cmds[++var->n];
			cmd[var->j].cmd_name[var->i] = '\0';
			cmd[var->j].cmd = ft_split(cmd->cmd_name, ' ');
		}
	}
	return (true);
}

	// int i = 0;
	// while(i <= var->j)
	// {
	// 	var->c = -1;
	// 	while (cmd[i].cmd[++var->c])
	// 		printf("%s\n", cmd[i].cmd[var->c]);
	// 	printf("------- \n");
	// 	i++;
	// }