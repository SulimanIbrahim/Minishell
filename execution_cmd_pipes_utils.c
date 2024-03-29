/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_pipes_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:40:08 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/28 03:41:02 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_process(t_input *input, t_var *var)
{
	var->c = 0;
	while (var->c < input->num_of_cmd)
	{
		wait(NULL);
		var->c++;
	}
}

void	close_fd(t_var *var)
{
	close(var->fd[0]);
	close(var->fd[1]);
}

void	init_all(t_var *var)
{
	var->splitted = NULL;
	var->temp = NULL;
	var->cmd_path = NULL;
}
