/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 05:12:06 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/17 08:44:20 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_srch_herdoc(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] && line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
			return (line + i);
		else if (!line[i])
			return (NULL);
		i++;
	}
	return (NULL);
}

static char	*remove_wrong_var_herdoc(char *line)
{
	t_var	var;
	char	*new_line;
	int		k;

	init_var(&var);
	k = (unsigned long)env_srch(line) - (unsigned long)line;
	var.i = k;
	var.c = var.i;
	while (line[var.i] && line[var.i] != ' '
		&& line[var.i] != '\'' && line[var.i] != '"')
		var.i++;
	var.n = var.i;
	while (line[var.i++])
		var.j++;
	var.len = var.j;
	new_line = malloc(var.c + var.len + 1);
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, line, var.c + 1);
	ft_strlcpy(new_line + var.c, line + var.n, var.len + 1);
	free(line);
	return (new_line);
}

static char	*replace_env_herdoc(char *line, char *env)
{
	t_var	var;
	char	*new_line;
	int		k;

	init_var(&var);
	k = (unsigned long)env_srch_herdoc(line) - (unsigned long)line;
	var.len = ft_strlen(ft_strchr(env, '=') + 1);
	var.c = k;
	var.i = var.c;
	while (line[var.c] && line[var.c] != ' '
		&& line[var.c] != '\'' && line[var.c] != '"')
		var.c++;
	var.j = 0;
	var.n = var.c;
	while (line[var.c++])
		var.j++;
	new_line = malloc(var.c + var.len + 2);
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, line, var.i + 1);
	ft_strlcpy(new_line + var.i, ft_strchr(env, '=') + 1, var.len + 1);
	ft_strlcpy(new_line + var.i + var.len, line + var.n, var.c + 1);
	free(line);
	return (new_line);
}

bool	check_env_herdoc(t_input *input, t_var *var)
{
	var->i = 0;
	var->j = 0;
	if (!var->temp || !var->temp[0])
		return (false);
	var->temp++;
	while (input->env[var->i])
	{
		if (input->env[var->i][var->j] == var->temp[var->j])
		{
			while (var->temp[var->j] && input->env[var->i][var->j]
				&& var->temp[var->j] == input->env[var->i][var->j])
				var->j++;
			if (input->env[var->i][var->j] == '=' && (!var->temp[var->j]
				|| var->temp[var->j] == ' ' || var->temp[var->j] == '"'
				|| var->temp[var->j] == '\'' || var->temp[var->j] == '\n'))
				return (true);
		}
		var->j = 0;
		var->i++;
	}
	return (false);
}

char	*expand_herdoc(char *line, t_input *input)
{
	t_var	var;

	var.i = 0;
	if (!line)
		return (NULL);
	if (!input || !env_srch_herdoc(line))
		return (line);
	var.temp = env_srch_herdoc(line) + 1;
	if (!var.temp)
		return (line);
	while (env_srch_herdoc(line))
	{
		var.temp = env_srch_herdoc(line);
		if (!var.temp)
			break ;
		if (check_env_herdoc(input, &var) == false)
			line = remove_wrong_var_herdoc(line);
		else
			line = replace_env_herdoc(line, input->env[var.i]);
		if (!env_srch_herdoc(line))
			break ;
	}
	return (line);
}
