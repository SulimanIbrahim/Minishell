/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:58:29 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/27 06:08:15 by ahibrahi         ###   ########.fr       */
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
		if (!new[j] && env[i][j] == '=')
			return (i);
		i++;
		j = 0;
	}
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

static	void	remove_env(t_input *input, int c)
{
	int		i;
	int		j;
	int		len;
	char	**tmp;

	i = 0;
	j = 0;
	len = env_len(input->env);
	tmp = malloc(sizeof(char *) * (len + 1));
	if (!tmp)
		return ;
	while (input->env[i])
	{
		if (i != c)
			tmp[j++] = ft_strdup(input->env[i]);
		free(input->env[i++]);
	}
	free(input->env);
	tmp[j] = NULL;
	input->env = tmp;
}

void	unset(t_cmd *cmd, t_input *input)
{
	t_var	var;

	var.i = 0;
	if (!cmd)
		return ;
	while (cmd->cmd[var.i])
	{
		if (ft_strchr(cmd->cmd[var.i], '='))
		{
			printf("unset: %s: invalid parameter name\n", cmd->cmd[var.i]);
			return ;
		}
		var.j = 0;
		var.j = env_search(cmd->cmd[var.i], input->env);
		if (var.j != 0)
			remove_env(input, var.j);
		var.i++;
	}
}
