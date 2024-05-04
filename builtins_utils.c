/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:42:00 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/22 22:24:05 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char *pwd, t_input *input)
{
	char	*temp;
	char	*temp2;

	if (!pwd)
		return ;
	if (!ft_get_env(pwd, input->env))
	{
		temp = getcwd(NULL, 0);
		temp2 = ft_strjoin(pwd, temp);
		add_env(temp2, input);
		(free(temp), free(temp2));
	}
	else
	{
		temp = getcwd(NULL, 0);
		temp2 = ft_strjoin(pwd, temp);
		replace_env(temp2, input, ft_get_env_index(pwd, input->env));
		(free(temp), free(temp2));
	}
	return ;
}

int	cd(t_cmd *cmd, t_input *input)
{
	if (cmd->cmd[2])
	{
		g_exit_num = 1;
		return (ft_printf (2, "cd: too many arguments\n"), 1);
	}
	update_pwd("OLDPWD=", input);
	if (!cmd || !cmd->cmd[1])
	{
		if (chdir(ft_get_env("HOME", input->env)) == -1)
			ft_printf (2, "cd: HOME not set\n");
	}
	else if (chdir(cmd->cmd[1]) == -1)
	{
		g_exit_num = 1;
		ft_printf (2, "cd: %s: no such file or directory\n", cmd->cmd[1]);
	}
	update_pwd("PWD=", input);
	return (1);
}

int	pwd(void)
{
	char	*str;

	str = NULL;
	str = getcwd(NULL, 0);
	if (str)
	{
		printf("%s\n", str);
		free(str);
	}
	g_exit_num = 0;
	return (1);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	if (!env || !env[0])
		return (1);
	while (env[i])
		printf("%s\n", env[i++]);
	g_exit_num = 0;
	return (1);
}

int	ft_exit(t_cmd **cmd, t_input *input, t_var *var)
{
	if (cmd && cmd[0] && cmd[0]->cmd[2])
	{
		g_exit_num = 1;
		ft_printf (2, "bash: exit: too many arguments\n");
	}
	else if (cmd && cmd[0])
	{
		if (str_is_digit(cmd[0]->cmd[1]) == 1)
		{
			g_exit_num = 2;
			ft_printf (2, "bash: exit: %s: numeric argument required\n",
				cmd[0]->cmd[1]);
		}
		else if (cmd[0]->cmd[1])
			g_exit_num = exit_atoi(cmd[0]->cmd[1]);
	}
	free_env(input->env);
	free_all(cmd, input, var);
	clear_history();
	exit (g_exit_num);
}
