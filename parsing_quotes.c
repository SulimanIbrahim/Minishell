/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 05:24:21 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/22 22:07:08 by ahibrahi         ###   ########.fr       */
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

static bool	check_double_quotes(char *line, t_var *var)
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
		ft_printf (2, "Syntax error : unclosed double quotes\n");
		return (false);
	}
	return (true);
}

static bool	check_single_quotes(char *line, t_var *var)
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
		ft_printf (2, "Syntax error : unclosed single quotes\n");
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
	return (true);
}
