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

char	*ft_get_env_path(char **env)
{
	if (!env)
		return (NULL);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0 && (*env)[4] == '=')
			return (*env + 5);
		env++;
	}
	return (NULL);
}
