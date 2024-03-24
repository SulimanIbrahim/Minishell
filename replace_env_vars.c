/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:43:11 by aken              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/16 06:39:42 by ahibrahi         ###   ########.fr       */
=======
/*   Updated: 2024/03/18 08:23:35 by aken             ###   ########.fr       */
>>>>>>> e71d4723a1539649c6a00d1d5adcb437bc40b619
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_srch(char *cmd)
{
	int	i;

<<<<<<< HEAD
	var->i = 0;
	var->j = 0;
	while (input->cmds[var->i] && input->cmds[var->i] != '$')
		var->i++;
	len_befor = var->i;
	while (input->cmds[var->i] && input->cmds[var->i] != ' ')
		var->i++;
	var->n = var->i;
	while (input->cmds[var->i++])
		var->j++;
	len_after = var->j;
	n_s = malloc(len_befor + len_after + 1);
	if (!n_s)
		return ;
	ft_strlcpy(n_s, input->cmds, len_befor + 1);
	ft_strlcpy(n_s + len_befor, input->cmds + var->n, len_after + 1);
	var->temp = input->cmds;
	free(var->temp);
	input->cmds = n_s;
=======
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
>>>>>>> e71d4723a1539649c6a00d1d5adcb437bc40b619
}

void	ft_remove_wrong_var(t_input *input)
{
<<<<<<< HEAD
	int		len_befor;
	int		len_after;
	char	*n_s;

	var->c = 0;
	var->n = 0;
	var->len = ft_strlen(ft_strchr(env, '=') + 1);
	while (input->cmds[var->c] && input->cmds[var->c] != '$')
		var->c++;
	len_befor = var->c;
	while (input->cmds[var->c] && input->cmds[var->c] != ' ')
		var->c++;
	var->n = var->c;
	while (input->cmds[var->c++])
		var->n++;
	len_after = var->n;
	n_s = malloc(len_befor + len_after + var->len + 1);
	if (!n_s)
		return ;
	ft_strlcpy(n_s, input->cmds, len_befor + 2);
	ft_strlcpy(n_s + len_befor, ft_strchr(env, '=') + 1, var->len + 1);
	ft_strlcpy(n_s + len_befor + var->len, input->cmds + var->n, len_after + 1);
	var->temp = input->cmds;
	free(var->temp);
	input->cmds = n_s;
=======
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
>>>>>>> e71d4723a1539649c6a00d1d5adcb437bc40b619
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
<<<<<<< HEAD
	if (!input->cmds[var->i] || !ft_strchr(input->cmds, '$'))
		return ;
	p = ft_strchr(input->cmds, '$') + 1;
	if (!p || p[var->i] == '(')
		return ;
=======
	if (!var->temp || !var->temp[0])
		return (false);
	var->temp++;
>>>>>>> e71d4723a1539649c6a00d1d5adcb437bc40b619
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
		if (!ft_strchr(input->cmds, '$'))
			return ;
		p = ft_strchr(input->cmds, '$') + 1;
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