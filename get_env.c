/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 05:45:43 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/18 22:18:07 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replace_num_error(t_input *input)
{
	t_var	var;
	char	*num;
	char	*new_cmd;

	init_var(&var);
	num = ft_itoa(g_exit_num);
	var.len = ft_strlen(num);
	var.c = env_srch(input->cmds) - input->cmds;
	var.i = var.c;
	while (input->cmds[var.c] && input->cmds[var.c] != ' '
		&& input->cmds[var.c] != '\'' && input->cmds[var.c] != '"')
		var.c++;
	var.n = var.c;
	while (input->cmds[var.c++])
		var.j++;
	new_cmd = malloc(var.i + var.j + var.len + 1);
	if (!new_cmd)
		return ;
	ft_strlcpy(new_cmd, input->cmds, var.i + 1);
	ft_strlcpy(new_cmd + var.i, num, var.len + 1);
	ft_strlcpy(new_cmd + var.i + var.len, input->cmds + var.n, var.j + 1);
	var.temp = input->cmds;
	free(var.temp);
	free(num);
	input->cmds = new_cmd;
}

int	env_len(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

int	ft_get_env_index(char *word, char **env)
{
	int	i;

	i = 0;
	if (!env || !word)
		return (0);
	while (env[i] != NULL)
	{
		if (ft_strncmp(*env, word, ft_strlen(word)) == 0
			&& (*env)[ft_strlen(word)] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_get_env(char *word, char **env)
{
	if (!env || !word)
		return (NULL);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, word, ft_strlen(word)) == 0
			&& (*env)[ft_strlen(word)] == '=')
			return (ft_strchr(*env, '=') + 1);
		env++;
	}
	return (NULL);
}
