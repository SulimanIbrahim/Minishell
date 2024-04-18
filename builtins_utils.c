/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:42:00 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/17 11:25:54 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd[1])
		return (chdir(getenv("HOME")));
	if (chdir(cmd->cmd[1]) == -1)
		printf("cd: no such file or directory: %s\n", cmd->cmd[1]);
	return (1);
}

int	pwd(void)
{
	return (printf("%s\n", getcwd(NULL, 0)));
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return (1);
}

int	ft_exit(t_cmd **cmd, t_input *input, t_var *var)
{
	int	len;

	if (cmd && cmd[0])
	{
		len = env_len(cmd[0]->cmd);
		printf("exit\n");
		if (len > 2)
			return (printf("bash: exit: too many arguments\n"));
		if (str_is_digit(cmd[0]->cmd[1]) == 1)
			printf("bash: exit: %s: numeric argument required\n",
				cmd[0]->cmd[1]);
		if (cmd[0]->cmd[1])
			g_exit_num = ft_atoi(cmd[0]->cmd[1]);
	}
	free_env(input->env);
	free_all(cmd, input, var);
	clear_history();
	exit (g_exit_num);
}
