/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:24:30 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/16 14:27:59 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum) 
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// there is problem in this function its not in the header
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

