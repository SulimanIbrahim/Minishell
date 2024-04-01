/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:29:36 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/01 06:15:54 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	check_command_ubstitution(t_input *input, t_var *var)
{
	var->i = 1;
	char 	q;
	char 	c;

	var->temp = ft_strchr(input->cmds, '$');
	while (var->temp)
	{
		if (!var->temp)
			return (true);
		if (var->temp[var->i] && (var->temp[var->i] == '\'' || var->temp[var->i] == '"'))
		{
			q = var->temp[var->i++];
			while (var->temp[var->i] && var->temp[var->i] != q)
			{
				if (var->temp[var->i] && (var->temp[var->i] == '(' || var->temp[var->i] == '{' || var->temp[var->i] == '['))
				{
					if (var->temp[var->i] == '(')
						c = var->temp[var->i] + 1;
					else
						c = var->temp[var->i] + 2;
					while (var->temp[var->i] && var->temp[var->i] != c)
					{
						if (var->temp[var->i] && var->temp[var->i] == q)
							return (printf("bash: syntax error near unexpected token\n"), false);
						var->i++;
					}
				}
				if (var->temp[var->i] && var->temp[var->i] == c)
					break ;
				var->i++;
			}
		}
		if (var->temp[var->i] && (var->temp[var->i] == '(' || var->temp[var->i] == '{' || var->temp[var->i] == '['))
			return (printf("bash: syntax error near unexpected token\n"), false);
		var->temp = ft_strchr(var->temp + var->i, '$');
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

	if (!pipe_quote_pars(input, &var))
		return (free_input(input), false);
	if (ft_check_redirections(input, &var))
		return (free_input(input), false);
	if (!check_command_ubstitution(input, &var))
		return (free_input(input), false);
	ft_check_env(input, &var);
	return (true);
}
