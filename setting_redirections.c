/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:07:34 by aken              #+#    #+#             */
/*   Updated: 2024/03/08 04:04:10 by aken             ###   ########.fr       */
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

t_enm	set_redirection_2(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '>')
	{
		if (input[++i] && input[i] == '>')
			return (APPEND);
		else
			return (OUTPUT);
	}
	else if (input[i] == '<')
	{
		if (input[++i] && input[i] == '<')
		{
			if (input[++i] && input[i] == '>')
				return (HERSTR);
			else
				return (HERDOC);
		}
	}
	return (INPUT);
}

char	*extracting_file_name(char *input, t_var *var)
{
	char	*file;

	var->n = 0;
	while (input[var->n] && input[var->n] != ' ')
		var->n++;
	file = malloc(var->n + 1);
	ft_strlcpy(file, input, var->n + 1);
	return (file);
}

void	set_redirection(t_input *input)
{
	t_var	var;

	if (!(ft_strchr(input->cmds, '<') || ft_strchr(input->cmds, '>')))
		return ;
	var.i = -1;
	while (input->cmds[++var.i])
	{
		if (input->cmds[var.i] == '\'' || input->cmds[var.i] == '"')
			var.i += skip(input->cmds + var.i, input->cmds[var.i]);
		if (input->cmds[var.i] == '>' || input->cmds[var.i] == '<')
		{
			var.j = var.i;
			input->redricts->type = set_redirection_2(input->cmds + var.i);
			var.i += skip(input->cmds + var.i, input->cmds[var.i]);
			var.i += skip(input->cmds + var.i, ' ');
			input->redricts->file_name = extracting_file_name(
					input->cmds + var.i, &var);
			var.temp = malloc(var.j + 1);
			ft_strlcpy(var.temp, input->cmds, var.j + 1);
			var.i += ft_strlen(input->redricts->file_name);
			input->cmds = ft_strjoin(var.temp, input->cmds + var.i);
			set_redirection(input);
		}
	}
}
