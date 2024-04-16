/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:42:46 by aken              #+#    #+#             */
/*   Updated: 2024/04/16 18:16:41 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_red(char *cmd_name)
{
	int		i;

	i = 0;
	while (cmd_name[i])
	{
		if (cmd_name[i] == '\'' || cmd_name[i] == '"')
			skip_quotes(cmd_name, &i, cmd_name[i]);
		if (cmd_name[i] && (cmd_name[i] == '>' || cmd_name[i] == '<'))
			return (cmd_name + i);
		else if (!cmd_name[i])
			return (NULL);
		i++;
	}
	return (NULL);
}

bool	ft_check_char_after_direction(char	*s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] && s[i] != PIPE)
	{
		if (s[i] == ' ' || s[i] == '<' || s[i] == '>')
			i++;
		else
			return (true);
	}
	return (false);
}

bool	ft_check_redirections_2(char *s, int *i, int j, char c)
{
	while (s[(*i)] == ' ')
		(*i)++;
	if (s[(*i)] == c)
	{
		(*i)++;
		j++;
	}
	if (s[(*i)] == c)
	{
		(*i)++;
		j++;
	}
	while (s[(*i)] == ' ')
		(*i)++;
	if (s[(*i)] == '<' || s[(*i)] == '>')
		return (false);
	(*i)--;
	return (true);
}

static	int	ft_s7lb(char *cmd_name, t_var *var, char c)
{
	if (!ft_check_redirections_2(cmd_name, &var->i, var->j, c)
		|| !ft_check_char_after_direction(cmd_name + var->i))
	{
		if (var->flag == 0)
			return (
				printf("bash:syntax error near unexpected token\n"));
		return (1);
	}
	return (0);
}

int	ft_check_redirections(char *cmd_name, t_var *var)
{
	var->i = -1;
	var->j = 1;
	if (!ft_check_red(cmd_name))
		return (0);
	while (cmd_name[++var->i])
	{
		if (cmd_name[var->i] == '\'' || cmd_name[var->i] == '"')
			skip_quotes(cmd_name, &var->i, cmd_name[var->i]);
		if (cmd_name[var->i])
			return (0);
		if (cmd_name[var->i] == '>' || cmd_name[var->i] == '<')
			if (ft_s7lb(cmd_name, var, cmd_name[var->i]))
				return (1);
	}
	return (0);
}
