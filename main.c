/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:25:22 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/22 23:10:58 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_num;

static bool	inite_structs(t_input *input, t_var *var, t_cmd ***cmd, char **env)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_memset(var, 0, sizeof(t_var));
	ft_memset(input, 0, sizeof(t_input));
	ft_memset(cmd, 0, sizeof(t_cmd));
	input->env = dup_shell(env);
	add_shlvl(input->env);
	return (true);
}

static bool	reading_line(t_input *input, t_var *var)
{
	input->num_of_cmd = 1;
	init_var(var);
	input->cmds = readline("\x1b[94mMinishell >> \x1b[0m");
	if (!input->cmds)
		ft_exit(NULL, input, var);
	add_history(input->cmds);
	return (true);
}

int	main(int ac, char **av, char **env)
{
	t_input	input;
	t_var	var;
	t_cmd	**cmd;

	(void)ac, (void)av;
	inite_structs(&input, &var, &cmd, env);
	while (1)
	{
		reading_line(&input, &var);
		if (parsing(&input))
		{
			cmd = ft_calloc(input.num_of_cmd, sizeof(t_cmd));
			cmd[input.num_of_cmd] = NULL;
			tokenize_cmds(&input, cmd, &var);
			if (cmd)
			{
				execute(cmd, &input, &var);
				free_all(cmd, &input, &var);
			}
		}
	}
	return (0);
}
