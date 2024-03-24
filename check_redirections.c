/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:42:46 by aken              #+#    #+#             */
/*   Updated: 2024/03/17 22:18:39 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip(char *cmds, char c)
{
	int	i;

	i = 0;
	while (cmds[i] && cmds[i] == c)
		i++;
	return (i);
}

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
	if (s[(*i)] == '<' && c == '<')
		(*i)++;
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

int	ft_check_redirections(t_input *input, t_var *var)
{
	var->i = -1;
	var->j = 1;
	if (!ft_check_red(input->cmds))
		return (0);
	while (input->cmds[++var->i])
	{
		if (input->cmds[var->i] == '\'' || input->cmds[var->i] == '"')
			skip_quotes(input->cmds, &var->i, input->cmds[var->i]);
		if (input->cmds[var->i] == '>')
		{
			if (!ft_check_redirections_2(input->cmds, &var->i, var->j, '>')
				|| !ft_check_char_after_direction(input->cmds + var->i))
				return (printf("bash: syntax error near unexpected token\n"));
		}
		else if (input->cmds[var->i] == '<')
		{
			if (!ft_check_redirections_2(input->cmds, &var->i, var->j, '<')
				|| !ft_check_char_after_direction(input->cmds + var->i))
				return (printf("bash: syntax error near unexpected token\n"));
		}
	}
	return (0);
}
