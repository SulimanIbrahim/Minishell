/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:58:29 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/23 05:54:09 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_search(char *new, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!new || !new[0])
		return (0);
	while (env[i])
	{
		while (new[j] && env[i][j] && env[i][j] != '=' && new[j] == env[i][j])
			j++;
		if (new[j] == '=' && env[i][j] == '=')
			return (i);
		i++;
		j = 0;
	}
	return (0);
}

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	add_env(char *new, int len, t_input *input)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (len + 2));
	while (input->env[i])
	{
		tmp[i] = ft_strdup(input->env[i]);
		free(input->env[i++]);
	}
	free(input->env);
	tmp[i++] = ft_strdup(new);
	tmp[i] = NULL;
	input->env = tmp;
}

void	replace_env(char *new, t_input *input, int i)
{
	char	*tmp;
	int		c;

	c = 5;
	if (!ft_strncmp(new, input->env[i], c))
	{
		while (new[++c])
		{
			if (!ft_isdigit(new[c]))
				break ;
		}
		if (c == 6 || new[c])
		{
			tmp = input->env[i];
			free(tmp);
			input->env[i] = ft_strdup("SHLVL=0");
			return ;
		}
	}
	tmp = input->env[i];
	free(tmp);
	input->env[i] = ft_strdup(new);
}

void	export(char *s, t_input *input)
{
	t_var	var;
	char	**tmp;

	var.i = 0;
	tmp = ft_split(s, ' ');
	if (!tmp)
		return ;
	while (tmp[var.i])
	{
		var.j = 0;
		if (ft_strchr(tmp[var.i], '='))
		{
			var.j = env_search(tmp[var.i], input->env);
			if (var.j != 0)
				replace_env(tmp[var.i], input, var.j);
			else
			{
				var.len = env_len(input->env);
				add_env(tmp[var.i], var.len, input);
			}
		}
		var.i++;
	}
}
