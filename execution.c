/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:17:41 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/17 01:52:32 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool execute(t_cmd **cmd, t_input *input)
{
	int i = 0;
	int id = 0;
	int status;
    char    **path;
	char *command;
    struct stat buffer;

	i = -1;
	// while (++i < input->num_of_cmd)
	// {
		// if (id == 0)
		// 	exit(0);
		id = fork();
		if (id != 0)
		{
            path = ft_split(ft_strdup(getenv("PATH")), ':');
            while (path[i])
            {
                if (stat(ft_strjoin(path[i], cmd[0]->cmd[0]), &buffer))
                    break ;
                else
                    i++;
            }
            if (!path[i])
				printf("shell : command not found !!!\n");
            else
            {
                command = ft_strjoin(path[i], cmd[0]->cmd[0]);
                if (execve(cmd[0]->cmd[0], cmd[0]->cmd + 1, input->env) == -1)
                    printf("shell : command not found !!!\n");
            }
            exit(0);
        }
	// }
	wait(&status);
	return (true);
}