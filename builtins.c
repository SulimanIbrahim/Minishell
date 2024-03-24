/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 05:38:39 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/24 21:06:36 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**init_bulitins(void)
{
	char	**builtins;

	builtins = malloc(sizeof(char *) * 7);
	if (!builtins)
		return (NULL);
	builtins[0] = ft_strdup("cd");
	builtins[1] = ft_strdup("echo");
	builtins[2] = ft_strdup("pwd");
	builtins[3] = ft_strdup("export");
	builtins[4] = ft_strdup("unset");
	builtins[5] = ft_strdup("env");
	builtins[6] = NULL;
	return (builtins);
}

bool	ft_exec_builtin(char *s, int i, t_input *input)
{
	if (i == 0)
		return (cd(s));
	else if (i == 1)
		return (echo(s));
	else if (i == 2)
		return (pwd());
	else if (i == 3)
		export(s, input);
	else if (i == 4)
		unset(s, input);
	else if (i == 5)
		return (ft_env(input->env));
	return (true);
}

bool	ft_check_builtins(t_cmd *cmd, t_input *input)
{
	int		i;
	int		j;
	char	**builtins;

	i = 0;
	j = 0;
	builtins = init_bulitins();
	while (builtins && builtins[i])
	{
		if (builtins[i][j] == cmd->cmd_name[j])
		{
			while (cmd->cmd_name[j] && builtins[i][j]
					&& cmd->cmd_name[j] != ' '
					&& cmd->cmd_name[j] == builtins[i][j])
				j++;
			if (!builtins[i][j]
				&& (!cmd->cmd_name[j] || cmd->cmd_name[j] == ' '))
				return (ft_exec_builtin(cmd->cmd_name + j, i, input));
		}
		j = 0;
		i++;
	}
	free_split(builtins);
	return (false);
}
