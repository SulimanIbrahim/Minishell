/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:29:36 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/03 05:08:10 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool	check_double_quotes(char *line, t_var *var)
{
	while (line[var->i])
	{
		if (line[var->i] == DOUBLE_QUOTE)
		{
			var->closed = 1;
			break ;
		}
		var->i++;
	}
	if (var->closed == 0)
	{
		printf("Syntax error : unclosed double quotes\n");
		return (false);
	}
	return (true);
}

bool	check_single_quotes(char *line, t_var *var)
{
	while (line[var->i])
	{
		if (line[var->i] == SINGLE_QUOTE)
		{
			var->closed = 1;
			break ;
		}
		var->i++;
	}
	if (var->closed == 0)
	{
		printf("Syntax error : unclosed single quotes\n");
		return (false);
	}
	return (true);
}

bool	quote_parsing(char *line, t_var *var)
{
	var->i = -1;
	while (line[++var->i])
	{
		var->closed = 0;
		if (line[var->i] == DOUBLE_QUOTE || line[var->i] == SINGLE_QUOTE)
		{
			if (line[var->i] == DOUBLE_QUOTE)
			{
				var->i++;
				if (!check_double_quotes(line, var))
					return (false);
			}
			else if (line[var->i] == SINGLE_QUOTE)
			{
				var->i++;
				if (!check_single_quotes(line, var))
					return (false);
			}
		}
	}
	return (true);
}

bool	pipe_parsing(t_input *input, t_var *var)
{
	var->i = -1;
	while (input->cmds[++var->i])
	{
		while (input->cmds[var->i] == ' ')
			var->i++;
		if (input->cmds[var->i] == PIPE)
			return (printf("Syntax error : unexpected pipe \n"), false);
		while (input->cmds[var->i])
		{
			if (input->cmds[var->i++] == PIPE)
			{
				input->num_of_cmd++;
				while (input->cmds[var->i] == ' ')
					var->i++;
				if (input->cmds[var->i + 1] == '\0'
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

	if (!pipe_quote_pars(input, &var))
		return (false);
	return (true);
}
