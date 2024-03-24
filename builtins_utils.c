/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:42:00 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/24 20:42:37 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (!s || !s[i])
		chdir("HOME");
	else
		chdir(s + i);
	return (1);
}

int	echo(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] && s[i] == '-' && s[i + 1] == 'n')
	{
		i += 2;
		while (s[i] && s[i] == ' ')
			i++;
		flag = 1;
	}
	while (s[i])
	{
		if (s[i] != '"' && s[i] != '\'')
			write(1, &s[i], 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (1);
}

int	pwd(void)
{
	return (printf("%s\n", getenv("PWD")));
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		echo(env[i++]);
	return (1);
}
