/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:19:23 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/16 02:55:52 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_n(char *line)
{
	int		i;

	i = 0;
	if ((line[i] != '-' || line[i + 1] != 'n'))
		return (false);
	i++;
	while (line[i] && line[i] == 'n')
		i++;
	if (line[i] == '\0')
		return (true);
	return (true);
}

static void	print_lines(char **lines, bool n_flag, int i, int j)
{
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] && lines[i][j + 1] &&
				lines[i][j] == '$' && lines[i][j + 1] == '?')
			{
				ft_putnbr_fd(g_exit_num, STDOUT_FILENO);
				j++;
			}
			else
				ft_putchar_fd(lines[i][j], STDOUT_FILENO);
			j++;
		}
		if (lines[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!lines[i + 1] && !n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

bool	echo(char **cmd)
{
	t_var	var;

	var.nflag = false;
	var.i = 0;
	var.j = 0;
	while (cmd[++var.i] && check_n(cmd[var.i]))
		var.nflag = true;
	if (!cmd[var.i])
	{
		if (!var.nflag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return (true);
	}
	print_lines(cmd, var.nflag, var.i, var.j);
	return (true);
}
