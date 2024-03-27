/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 05:38:39 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/27 09:01:02 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && !(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '-' && str[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

static	char	**init_bulitins(void)
{
	char	**builtins;

	builtins = malloc(sizeof(char *) * 7);
	if (!builtins)
		return (NULL);
	builtins[0] = ft_strdup("cd");
	builtins[1] = ft_strdup("pwd");
	builtins[2] = ft_strdup("export");
	builtins[3] = ft_strdup("unset");
	builtins[4] = ft_strdup("env");
	builtins[5] = ft_strdup("exit");
	builtins[6] = NULL;
	// builtins[7] = ft_strdup("echo");
	return (builtins);
}

bool	ft_exec_builtin(t_cmd *cmd, int i, t_input *input)
{
	if (i == 0)
		return (cd(cmd));
	// else if (i == 1)
	// 	return (echo(s));
	else if (i == 1)
		return (pwd());
	else if (i == 2)
		export(cmd, input);
	else if (i == 3)
		unset(cmd, input);
	else if (i == 4)
		return (ft_env(input->env));
	else if (i == 5)
		return (ft_exit(cmd));
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
	while (builtins && builtins[i] && cmd->cmd[0])
	{
		if (builtins[i][j] == cmd->cmd[0][j])
		{
			while (cmd->cmd[0][j] && builtins[i][j]
					&& cmd->cmd[0][j] != ' '
					&& cmd->cmd[0][j] == builtins[i][j])
				j++;
			if (!builtins[i][j]
				&& (!cmd->cmd[0][j] || cmd->cmd[0][j] == ' '))
				return (ft_exec_builtin(cmd, i, input));
		}
		j = 0;
		i++;
	}
	free_split(builtins);
	return (false);
}
