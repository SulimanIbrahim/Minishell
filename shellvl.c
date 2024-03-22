/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellvl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:10:16 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/22 05:59:58 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_shell(char **env)
{
	t_var	var;
	char	**dup_shell;

	if (!env || !env[0])
		return (NULL);
	var.i = 0;
	while (env[var.i])
		var.i++;
	dup_shell = malloc(sizeof(char *) * (var.i + 1));
	var.i = -1;
	while (env[++var.i])
		dup_shell[var.i] = ft_strdup(env[var.i]);
	dup_shell[var.i] = NULL;
	return (dup_shell);
}

void	add_shlvl(char **env)
{
	t_var		var;

	var.i = 0;
	if (!env || !env[0])
		return ;
	while (env[var.i] && ft_strncmp(env[var.i], "SHLVL", 5))
		var.i++;
	if (!env[var.i])
		return ;
	var.n = ft_atoi(ft_strchr(env[var.i], '=') + 1);
	var.temp = env[var.i];
	free(var.temp);
	env[var.i] = ft_strdup(ft_strjoin("SHLVL=", ft_itoa(var.n + 1)));
}
