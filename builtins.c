/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 05:38:39 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/16 16:31:35 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_exit(t_cmd **cmd, t_input *input, t_var *var, int n)
{
	int		i;

	i = 0;
	if (cmd && cmd[n] && cmd[n]->cmd[0] && "exit"[i] == cmd[n]->cmd[0][i])
	{
		while (cmd[n]->cmd[0][i] && "exit"[i]
				&& cmd[n]->cmd[0][i] != ' '
				&& cmd[n]->cmd[0][i] == "exit"[i])
			i++;
		if (!"exit"[i]
			&& (!cmd[n]->cmd[0][i] || cmd[n]->cmd[0][i] == ' '))
			ft_exit(cmd, input, var);
	}
	return ;
}

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
	builtins[5] = ft_strdup("echo");
	builtins[6] = NULL;
	return (builtins);
}

bool	ft_exec_builtin(t_cmd *cmd, int i, t_input *input)
{
	if (i == 0)
		cd(cmd, input);
	else if (i == 1)
		pwd();
	else if (i == 2)
		export(cmd, input);
	else if (i == 3)
		unset(cmd, input);
	else if (i == 4)
		ft_env(input->env);
	else if (i == 5)
		echo(cmd->cmd);
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
				return (free_split(builtins), ft_exec_builtin(cmd, i, input));
		}
		j = 0;
		i++;
	}
	free_split(builtins);
	return (false);
}
