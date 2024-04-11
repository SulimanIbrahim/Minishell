/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:43:11 by aken              #+#    #+#             */
/*   Updated: 2024/04/01 05:48:37 by ahibrahi         ###   ########.fr       */
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
		if (cmd[i] == '\'')
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
	char	*new_cmd;

	init_var(&var);
	var.i = env_srch(input->cmds) - input->cmds;
	var.c = var.i;
	while (input->cmds[var.i] && input->cmds[var.i] != ' '
		&& input->cmds[var.i] != '\'' && input->cmds[var.i] != '"')
		var.i++;
	var.n = var.i;
	while (input->cmds[var.i++])
		var.j++;
	var.len = var.j;
	new_cmd = malloc(var.c + var.len + 1);
	if (!new_cmd)
		return ;
	ft_strlcpy(new_cmd, input->cmds, var.c + 1);
	ft_strlcpy(new_cmd + var.c, input->cmds + var.n, var.len + 1);
	var.temp = input->cmds;
	free(var.temp);
	input->cmds = new_cmd;
}

void	ft_replace_env(t_input *input, char *env)
{
	t_var	var;
	char	*new_cmd;

	init_var(&var);
	var.len = ft_strlen(ft_strchr(env, '=') + 1);
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
	ft_strlcpy(new_cmd + var.i, ft_strchr(env, '=') + 1, var.len + 1);
	ft_strlcpy(new_cmd + var.i + var.len, input->cmds + var.n, var.j + 1);
	var.temp = input->cmds;
	free(var.temp);
	input->cmds = new_cmd;
}

bool	ft_check_env2(t_input *input, t_var *var)
{
	var->i = 0;
	var->j = 0;
	if (!var->temp || !var->temp[0])
		return (false);
	var->temp++;
	while (input->env[var->i])
	{
		if (input->env[var->i][var->j] == var->temp[var->j])
		{
			while (var->temp[var->j] && input->env[var->i][var->j]
				&& var->temp[var->j] == input->env[var->i][var->j])
				var->j++;
			if (input->env[var->i][var->j] == '=' && (!var->temp[var->j]
				|| var->temp[var->j] == ' ' || var->temp[var->j] == '"'
				|| var->temp[var->j] == '\''))
			{
				ft_replace_env(input, input->env[var->i]);
				return (true);
			}
		}
		var->j = 0;
		var->i++;
	}
	return (false);
}

void	ft_check_env(t_input *input, t_var *var)
{
	if (!input->cmds || !env_srch(input->cmds))
		return ;
	var->temp = env_srch(input->cmds) + 1;
	if (!var->temp)
		return ;
	while (env_srch(input->cmds))
	{
		var->temp = env_srch(input->cmds);
		if (!var->temp)
			return ;
		if (ft_check_env2(input, var) == false)
			ft_remove_wrong_var(input);
		if (!env_srch(input->cmds))
			break ;
	}
}
// try this case (ls $PWD  $ $P T $HOME $PATH"k" ls)