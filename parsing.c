/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:29:36 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/10 05:32:02 by aken             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(t_input *input, int *i, int q_type)
{
	if (input->cmds[*i] == q_type)
		(*i)++;
	while (input->cmds[*i] != q_type && input->cmds[*i])
		(*i)++;
}

bool	pipe_parsing(t_input *input, t_var *var)
{
	var->i = -1;
	while (input->cmds[++var->i])
	{
		while (input->cmds[var->i] == ' ')
			var->i++;
		if (input->cmds[var->i] == PIPE)
			return (printf("Syntax error : unexpected pipe 1\n"), false);
		while (input->cmds[var->i])
		{
			if (input->cmds[var->i] == DOUBLE_QUOTE)
				skip_quotes(input, &var->i, DOUBLE_QUOTE);
			if (input->cmds[var->i] == SINGLE_QUOTE)
				skip_quotes(input, &var->i, SINGLE_QUOTE);
			if (input->cmds[var->i++] == PIPE)
			{
				input->num_of_cmd++;
				while (input->cmds[var->i] == ' ')
					var->i++;
				if (input->cmds[var->i] == '\0'
					|| input->cmds[var->i] == PIPE)
					return (printf("Syntax error : unexpected pipe \n"), false);
			}
		}
	}
	return (true);
}

bool	pipe_quote_pars(t_input *input, t_var *var)
{
	if (!quote_parsing(input->cmds, var))
		return (false);
	if (!pipe_parsing(input, var))
		return (false);
	return (true);
}

bool	parsing(t_input *input)
{
	t_var	var;

	if (!pipe_quote_pars(input, &var)
		|| ft_check_redirections(input, &var) != 0)
		return (false);
	ft_check_env(input, &var);
	return (true);
}
