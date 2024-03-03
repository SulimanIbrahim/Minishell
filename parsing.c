/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:29:36 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/03 05:23:36 by suibrahi         ###   ########.fr       */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pipe_parsing(t_input *input, t_var *var)
{
	var->i = -1;
	while (input->cmds[++var->i])
	{
		while (input->cmds[var->i] == ' ')
			var->i++;
		if (input->cmds[var->i] == PIPE)
			return (printf("Syntax error : unexpected pipe \n"), false);
		while (input->cmds[var->i])
		{
			if (input->cmds[var->i++] == PIPE)
			{
				input->num_of_cmd++;
				while (input->cmds[var->i] == ' ')
					var->i++;
				if (input->cmds[var->i + 1] == '\0'
					|| input->cmds[var->i] == PIPE)
					return (printf("Syntax error : unexpected pipe \n"), false);
			}
		}
	}
	return (true);
}

bool	pipe_quote_pars(t_input *input, t_var *var)
{
	if (!quote_parsing(input->cmds, var))
		return (false);
	if (!pipe_parsing(input, var))
		return (false);
	return (true);
}

bool	parsing(t_input *input)
{
	t_var	var;

	if (!pipe_quote_pars(input, &var)
		|| ft_check_redirections(input, &var) != 0)
		return (false);
	ft_check_env(input, &var);
	return (true);
}
