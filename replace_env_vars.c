/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:43:11 by aken              #+#    #+#             */
/*   Updated: 2024/03/16 05:41:56 by aken             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_wrong_var(t_input *input, t_var *var)
{
	int		len_befor;
	int		len_after;
	char	*n_s;

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
}

void	ft_replace_env(t_input *input, char *env, t_var *var)
{
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
}

void	ft_check_env(t_input *input, t_var *var)
{
	char	*p;

	var->i = 0;
	var->j = 0;
	if (!input->cmds[var->i] || !ft_strchr(input->cmds, '$'))
		return ;
	p = ft_strchr(input->cmds, '$') + 1;
	if (!p || p[var->i] == '(')
		return ;
	while (input->env[var->i])
	{
		if (input->env[var->i][var->j] == p[var->j])
		{
			while (p[var->j] && input->env[var->i][var->j] && p[var->j] != ' '
				&& p[var->j] == input->env[var->i][var->j])
				var->j++;
			if (input->env[var->i][var->j] == '=' && (!p[var->j]
				|| p[var->j] == ' '))
				ft_replace_env(input, input->env[var->i], var);
		}
		if (!ft_strchr(input->cmds, '$'))
			return ;
		p = ft_strchr(input->cmds, '$') + 1;
		var->j = 0;
		var->i++;
	}
	ft_remove_wrong_var(input, var);
}
