/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:58:29 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/27 06:04:37 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	env_search(char *new, char **env)
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

static	void	add_env(char *new, int len, t_input *input)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return ;
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

static	void	replace_env(char *new, t_input *input, int i)
{
	char	*tmp;

	tmp = input->env[i];
	free(tmp);
	input->env[i] = ft_strdup(new);
}

void	export(t_cmd *cmd, t_input *input)
{
	t_var	var;

	var.i = 0;
	if (!cmd)
		return ;
	while (cmd->cmd[var.i])
	{
		var.j = 0;
		if (ft_strchr(cmd->cmd[var.i], '='))
		{
			var.j = env_search(cmd->cmd[var.i], input->env);
			if (var.j != 0)
				replace_env(cmd->cmd[var.i], input, var.j);
			else
			{
				var.len = env_len(input->env);
				add_env(cmd->cmd[var.i], var.len, input);
			}
		}
		var.i++;
	}
}
