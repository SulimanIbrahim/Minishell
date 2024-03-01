/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:29:36 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/29 00:18:24 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	quote_parsing(char *line)
{
	int	i;
	int	closed;

	i = 0;
	while (line[i])
	{
		closed = 0;
		if (line[i] == DOUBLE_QUOTE || line[i] == SINGLE_QUOTE)
		{
			if (line[i] == DOUBLE_QUOTE)
			{
				i++;
				while (line[i])
				{
					if (line[i] == DOUBLE_QUOTE)
					{
						closed = 1;
						break ;
					}
					i++;
				}
				if (closed == 0)
				{
					printf("Syntax error : unclosed double quotes\n");
					return (false);
				}
			}
			else if (line[i] == SINGLE_QUOTE)
			{
				i++;
				while (line[i])
				{
					if (line[i] == SINGLE_QUOTE)
					{
						closed = 1;
						break ;
					}
					i++;
				}
				if (closed == 0)
				{
					printf("Syntax error : unclosed single quotes\n");
					return (false);
				}
			}
		}
		i++;
	}
	return (true);
}

bool	pipe_parsing(t_input *input)
{
	int	i;

	i = 0;
	while (input->cmds[i])
	{
		while (input->cmds[i] == ' ')
			i++;
		if (input->cmds[i] == PIPE)
		{
			printf("Syntax error : unexpected pipe \n");
			return (false);
		}
		while (input->cmds[i])
		{
			if (input->cmds[i++] == PIPE)
			{
				input->num_of_cmd++;
				while (input->cmds[i] == ' ')
					i++;
				if (input->cmds[i + 1] == '\0' || input->cmds[i] == PIPE)
				{
					printf("Syntax error : unexpected pipe\n");
					return (false);
				}
			}
		}
		i++;
	}
	return (true);
}

bool	pipe_quote_pars(t_input *input)
{
	if (!quote_parsing(input->cmds))
		return (false);
	if (!pipe_parsing(input))
		return (false);
	return (true);
}

bool	parsing(t_input *input)
{
	if (!pipe_quote_pars(input))
		return (false);
	return (true);
}
