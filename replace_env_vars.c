/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:43:11 by aken              #+#    #+#             */
/*   Updated: 2024/03/18 08:34:07 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_srch(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			skip_quotes(cmd, &i, cmd[i]);
		if (cmd[i] && cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] != ' ')
			return (cmd + i);
		else if (!cmd[i])
			return (NULL);
		i++;
	}
	return (NULL);
}

void	ft_remove_wrong_var(t_input *input)
{
	t_var	var;
	char	*new_line;

	var.i = 0;
	var.j = 0;
	while (input->cmds[var.i] && input->cmds[var.i] != '$')
		var.i++;
	var.c = var.i;
	while (input->cmds[var.i] && input->cmds[var.i] != ' ')
		var.i++;
	var.n = var.i;
	while (input->cmds[var.i++])
		var.j++;
	var.n = var.j;
	new_line = malloc(var.c + var.n + 1);
	if (!new_line)
		return ;
	ft_strlcpy(new_line, input->cmds, var.c + 1);
	ft_strlcpy(new_line + var.c, input->cmds + var.n, var.n + 1);
	var.temp = input->cmds;
	free(var.temp);
	input->cmds = new_line;
}

void	ft_replace_env(t_input *input, char *env)
{
	t_var	var;
	char	*new_line;

	var.c = 0;
	var.n = 0;
	var.len = ft_strlen(ft_strchr(env, '=') + 1);
	while (input->cmds[var.c] && input->cmds[var.c] != '$')
		var.c++;
	var.i = var.c;
	while (input->cmds[var.c] && input->cmds[var.c] != ' ')
		var.c++;
	var.n = var.c;
	while (input->cmds[var.c++])
		var.n++;
	var.j = var.n;
	new_line = malloc(var.i + var.j + var.len + 1);
	if (!new_line)
		return ;
	ft_strlcpy(new_line, input->cmds, var.i + 2);
	ft_strlcpy(new_line + var.i, ft_strchr(env, '=') + 1, var.len + 1);
	ft_strlcpy(new_line + var.i + var.len, input->cmds + var.n, var.j + 1);
	var.temp = input->cmds;
	free(var.temp);
	input->cmds = new_line;
}

void	ft_check_env(t_input *input, t_var *var)
{
	var->i = 0;
	var->j = 0;
	if (!input->cmds || !env_srch(input->cmds))
		return ;
	printf("%s\n", );
	while (env_srch(input->cmds))
	{
		var->temp = env_srch(input->cmds) + 1;
		if (!var->temp)
			return ;
		while (input->env[var->i])
		{
			if (input->env[var->i][var->j] == var->temp[var->j])
			{
				while (var->temp[var->j] && input->env[var->i][var->j]
					&& var->temp[var->j] == input->env[var->i][var->j])
					var->j++;
				if (input->env[var->i][var->j] == '=' && (!var->temp[var->j]
					|| var->temp[var->j] == ' '))
				{
					ft_replace_env(input, input->env[var->i]);
					if (!env_srch(input->cmds))
						break ;
					var->temp = env_srch(input->cmds) + 1;
				}
			}
			var->j = 0;
			var->i++;
		}
		if (!env_srch(input->cmds))
			break ;
		if (var->temp == env_srch(input->cmds) + 1)
			ft_remove_wrong_var(input);
		var->i = 0;
	}
}
