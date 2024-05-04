/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:58:29 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/22 23:46:26 by suibrahi         ###   ########.fr       */
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
		return (-1);
	while (env[i])
	{
		while (new[j] && env[i][j] && env[i][j] != '=' && new[j] == env[i][j])
			j++;
		if (new[j] == '=' && env[i][j] == '=')
			return (i);
		i++;
		j = 0;
	}
	return (-1);
}

void	add_env(char *new, t_input *input)
{
	int		i;
	int		len;
	char	**tmp;

	i = 0;
	if (!new || !input)
		return ;
	len = env_len(input->env);
	tmp = malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return ;
	while (input->env[i])
	{
		tmp[i] = ft_strdup(input->env[i]);
		free(input->env[i++]);
	}
	if (input->env)
		free(input->env);
	tmp[i++] = ft_strdup(new);
	tmp[i] = NULL;
	input->env = tmp;
}

void	replace_env(char *new, t_input *input, int i)
{
	char	*tmp;

	if (!new || !input || !input->env || !input->env[i])
		return ;
	tmp = input->env[i];
	free(tmp);
	input->env[i] = ft_strdup(new);
}

static void	print_export(t_input *input)
{
	int	i;

	i = 0;
	while (input->env[i])
	{
		printf("declare -x %s\n", input->env[i]);
		i++;
	}
}

int	check_identifier(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i] == '-' || ft_isdigit(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

void	export(t_cmd *cmd, t_input *input)
{
	t_var	var;

	var.i = -1;
	if (!cmd || !cmd->cmd || !input || !input->env)
		return ;
	if (cmd && !cmd->cmd[1])
		return (print_export(input));
	while (cmd->cmd[++var.i])
	{
		if (cmd->cmd[var.i][0] == '=' || check_identifier(cmd->cmd[var.i]) == 0)
			return ((void)ft_printf (2, "unset: '%s': not a valid identifier\n"
					, cmd->cmd[var.i]), (void)(g_exit_num = 1));
		if (ft_strchr(cmd->cmd[var.i], '='))
		{
			var.j = -1;
			var.j = env_search(cmd->cmd[var.i], input->env);
			if (var.j != -1)
				replace_env(cmd->cmd[var.i], input, var.j);
			else
				add_env(cmd->cmd[var.i], input);
		}
	}
}
