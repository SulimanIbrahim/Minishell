/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:25:22 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/01 17:09:59 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *cpy_name(t_input *input)
{
	int		i;
	int		size;
	char	*name;

	i = 0;
	size = 0;
	if (*input->cmds == PIPE)
		input->cmds++;
	while (input->cmds[size] != PIPE && input->cmds[size])
		size++;
	name = malloc((size + 1) * sizeof(char));
	if (!name)
		return (NULL);
	while (*input->cmds != PIPE && *input->cmds)
	{
		name[i] = *input->cmds;
		input->cmds++;
		i++;
	}
	name[i] = '\0';
	return (name);
}


bool	tokenize(t_input *input, t_cmd *cmd)
{
	int	i;

	i = 0;

	while (i < input->num_of_cmd)
	{
		cmd[i].cmd_name = cpy_name(input);
		// printf("%s\n", cmd[i].cmd_name);
		i++;
	}
	return (true);
}

bool execute(t_cmd *cmd, t_input *input, char **env)
{
	int i = 0;
	int id = 1;
	int status;
	char *command;

	env = NULL;
	i = -1;
	while (++i < input->num_of_cmd)
	{
		if (id == 0)
			exit(0);
		id = fork();
		if (id == 0)
		{
			command = ft_strjoin("/bin/", cmd[i].cmd_name);
			if (execve(command, &cmd[i].cmd_name, env) == -1)
				printf("shell : command not found !!!\n");
			exit(0);
		}
	}
	wait(&status) > 0;
	return (true);
}

int main (int ac, char **av, char **env)
{
	t_input	input;
	t_cmd	*cmd;

	(void)av;
	(void)ac;
	while (1)
	{
		input.num_of_cmd = 1;
		input.cmds = readline("\x1b[94mMinishell >> \x1b[0m");
		add_history(input.cmds);
		if (parsing(&input))
		{
			cmd = (t_cmd *)ft_calloc(input.num_of_cmd, sizeof(t_cmd));
			if (cmd)
			{
				tokenize(&input, cmd);
				if (execute(cmd, &input, env))
					continue ;
			}
			else
				continue ;
		}
		continue ;
	}
	return (0);
}
