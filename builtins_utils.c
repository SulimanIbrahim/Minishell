/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:42:00 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/01 06:22:06 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd[1])
		chdir(getenv("HOME"));
	else if (chdir(cmd->cmd[1]) == -1)
		printf("cd: no such file or directory: %s\n", cmd->cmd[1]);
	return (1);
}

// int	echo(t_input *input)
// {
// 	int		i;
// 	int		flag;
// 	char	*p;

// 	i = 0;
// 	flag = 0;
// 	p = ft_strchr(input->cmds, ' ');
// 	while (*p && *p == ' ')
// 		p++;
// 	if (p[i] && p[i++] == '-')
// 	{
// 		if (p[i] && p[i++] == 'n')
// 		{
// 			if (!p[i] || p[i] == ' ')
// 			{
// 				flag = 1;
// 				p += i;
// 			}
// 		}
// 	}
// 	while (*p && *p == ' ')
// 		p++;
// 	printf("%s", p);
// 	if (flag != 1)
// 		printf("\n");
// 	return (1);
// }

int	pwd(void)
{
	return (printf("%s\n", getenv("PWD")));
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	int	len;

	len = env_len(cmd->cmd);
	printf("exit\n");
	if (len > 2)
		return (printf("bash: exit: too many arguments\n"));
	if (str_is_digit(cmd->cmd[1]) == 1)
		printf("bash: exit: %s: numeric argument required\n", cmd->cmd[1]);
	if (cmd->cmd[1])
		exit (ft_atoi(cmd->cmd[1]));
	exit (0);
}
