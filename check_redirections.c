/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:42:46 by aken              #+#    #+#             */
/*   Updated: 2024/03/12 05:52:32 by ahibrahi         ###   ########.fr       */
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

int	ft_check_redirections_2(char *s, int j, char c)
{
	int		i;

	i = 0;
	if (s[i] == '<' && c == '<')
		i++;
	while (s[i] == ' ')
		i++;
	if (s[i] == c)
	{
		i++;
		j++;
	}
	if (s[i] == c)
	{
		i++;
		j++;
	}
	while (s[i] == ' ')
		i++;
	if (s[i] == '<' || s[i] == '>')
		return (0);
	return (i);
}

int	ft_check_redirections(t_input *input, t_var *var)
{
	var->i = -1;
	var->j = 1;
	if (!input->cmds[0]
		|| ((!ft_strchr(input->cmds, '>') && !ft_strchr(input->cmds, '<'))))
		return (0);
	while (input->cmds[++var->i])
	{
		if (input->cmds[var->i] == '\'' || input->cmds[var->i] == '"')
			skip_quotes(input, &var->i, input->cmds[var->i]);
		if (input->cmds[var->i] == '>')
		{
			var->j = ft_check_redirections_2(input->cmds + var->i, var->j, '>');
			if (var->j == 0
				|| !ft_check_char_after_direction(input->cmds + var->i))
				return (printf("bash: syntax error near unexpected token\n"));
			var->i += (var->j - 1);
		}
		else if (input->cmds[var->i] == '<')
		{
			var->j = ft_check_redirections_2(input->cmds + var->i, var->j, '<');
			if (var->j == 0
				|| !ft_check_char_after_direction(input->cmds + var->i))
				return (printf("bash: syntax error near unexpected token\n"));
			var->i += (var->j - 1);
		}
	}
	return (0);
}
