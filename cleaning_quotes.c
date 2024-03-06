/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:59:26 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/06 04:56:24 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	clean_quotes(t_input *input, t_var *var)
{
	var->i = -1;
	var->j = 0;
	var->temp = (char *)malloc((ft_strlen(input->cmds) + 1) * sizeof(char));
	if (!var->temp)
		return (false);
	while (input->cmds[++var->i])
	{
		if (input->cmds[var->i] == DOUBLE_QUOTE)
		{
			var->i++;
			while (input->cmds[var->i] != DOUBLE_QUOTE && input->cmds[var->i])
				var->temp[var->j++] = input->cmds[var->i++];
		}
		else if (input->cmds[var->i] == SINGLE_QUOTE)
		{
			var->i++;
			while (input->cmds[var->i] != SINGLE_QUOTE && input->cmds[var->i])
				var->temp[var->j++] = input->cmds[var->i++];
		}
		else
			var->temp[var->j++] = input->cmds[var->i];
	}
	var->temp[var->j] = '\0';
	input->cmds = var->temp;
	return (free(var->temp), true);
}
