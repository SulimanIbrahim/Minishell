/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:19:23 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/04 08:52:24 by ahibrahi         ###   ########.fr       */
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

static void	print_lines(char **lines, bool n_flag, int i)
{
	if (!lines[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (lines[i])
	{
		ft_putstr_fd(lines[i], STDOUT_FILENO);
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
	// if (ft_strncmp(cmd[1], "$?", 2) != 0)
	// {
	// 	printf("%d", exit_num);
	// 	exit_num = 0;
	// 	return (true);
	// }
	while (cmd[++var.i] && check_n(cmd[var.i]))
		var.nflag = true;
	print_lines(cmd, var.nflag, var.i);
	return (true);
}
