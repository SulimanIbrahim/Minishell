/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:29:36 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/16 18:37:08 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip(char *cmds, char c)
{
	int	i;

	i = 0;
	while (cmds[i] && (cmds[i] == c
			|| cmds[i] == '\t' || cmds[i] == '\v'))
		i++;
	return (i);
}

void	skip_quotes(char *input, int *i, int q_type)
{
	if (input[*i] == q_type)
		(*i)++;
	while (input[*i] != q_type && input[*i])
		(*i)++;
}

bool	pipe_parsing(t_input *input, t_var *var)
{
	var->i = 0;
	while (input->cmds[var->i] == ' ')
		var->i++;
	if (input->cmds[var->i] == PIPE)
		return (printf("Syntax error : unexpected pipe 1\n"), false);
	while (input->cmds[var->i])
	{
		if (input->cmds[var->i] == DOUBLE_QUOTE)
			skip_quotes(input->cmds, &var->i, DOUBLE_QUOTE);
		if (input->cmds[var->i] == SINGLE_QUOTE)
			skip_quotes(input->cmds, &var->i, SINGLE_QUOTE);
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

	var.flag = 0;
	if (!pipe_quote_pars(input, &var))
	{
		g_exit_num = 2;
		return (free_input(input), false);
	}
	if (ft_check_redirections(input->cmds, &var))
	{
		g_exit_num = 2;
		return (free_input(input), false);
	}
	var.flag = 1;
	ft_check_env(input, &var);
	return (true);
}
