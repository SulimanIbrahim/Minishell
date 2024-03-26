/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:25:22 by suibrahi          #+#    #+#             */
/*   Updated: 2024/03/26 06:22:56 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool execute_pipes(t_cmd **cmd, t_input *input, t_var *var)
{
	var->i = -1;
	var->j = -1;
	var->fdnum = -1;
	while (++var->i < input->num_of_cmd)
	{
		if (var->id == 0)
			exit(0);
		if (var->i % 2 == 0 && ((var->i + 1) != input->num_of_cmd))
			pipe(var->fd[++var->fdnum]);
		var->id = fork();
		if (var->id == 0)
		{

			if (var->i == 0)
			{
				if (dup2(var->fd[var->fdnum][1], STDOUT_FILENO) == -1)
					exit(1);
				close(var->fd[var->fdnum][0]);
				close(var->fd[var->fdnum][1]);
			}
			else if ((var->i + 1) == input->num_of_cmd)
			{
				if (dup2(var->fd[var->fdnum][0], STDIN_FILENO) == -1)
					exit(1);
				close(var->fd[var->fdnum][1]);
				close(var->fd[var->fdnum][0]);
			}
			else
			{
				if (dup2(var->fd[var->fdnum][0], STDIN_FILENO) == -1)
					exit(1);
				if (dup2(var->fd[var->fdnum][1], STDOUT_FILENO) == -1)
					exit(1);
				close(var->fd[var->fdnum][0]);
				close(var->fd[var->fdnum][1]);
			}
			if (ft_strchr(cmd[var->i]->cmd[0], '/') == NULL)
			{
				var->splitted = ft_split(getenv("PATH"), ':');
				while (var->splitted[++var->j])
				{
					var->temp = ft_strjoin(var->splitted[var->j], "/");
					var->cmd_path = ft_strjoin(var->temp, cmd[var->i]->cmd[0]);
					if (access(var->cmd_path, F_OK) == 0)
						break ;
					else if (var->splitted[var->i + 1] == NULL)
					{
						printf("(%s) command not found !!!\n", cmd[var->i]->cmd[0]);
						free_all(cmd, input, var);
						exit(1);
					}
					free(var->temp);
					free(var->cmd_path);
					var->temp = NULL;
					var->cmd_path = NULL;
				}
			}
			else
			{
				if (access(cmd[var->i]->cmd[0], F_OK) == -1)
				{
					printf("(%s) command not found !!!\n", cmd[var->i]->cmd[0]);
					exit(1);
				}
				else
					var->cmd_path = cmd[var->i]->cmd[0];
			}
			if (execve(var->cmd_path, cmd[var->i]->cmd, input->env) == -1)
				printf("(%s) command not found !!!\n", cmd[var->i]->cmd[0]);
			exit(0);
		}
	}
	var->i = -1;
	while(++var->i < (input->num_of_cmd / 2))
	{
		close(var->fd[var->fdnum][0]);
		close(var->fd[var->fdnum][1]);
	}
	while (wait(&var->status) > -1)
		;
		return (true);
}

bool execute(t_cmd **cmd, t_input *input, t_var *var)
{
	var->id = 1;
	var->i = 0;
	var->j = 0;
	var->cmd_path = NULL;
	var->splitted = NULL;
	var->temp = NULL;
	if (input->num_of_cmd == 1)
	{
		if (fork() == 0)
		{
			if (ft_strchr(cmd[var->i]->cmd[0], '/') == NULL)
			{
				var->splitted = ft_split(getenv("PATH"), ':');
				while (var->splitted[++var->i])
				{
					var->temp = ft_strjoin(var->splitted[var->i], "/");
					var->cmd_path = ft_strjoin(var->temp, cmd[0]->cmd[0]);
					if (access(var->cmd_path, F_OK) == 0)
						break ;
					else if (var->splitted[var->i + 1] == NULL)
					{
						printf("command not found !!\n");
						free_all(cmd, input, var);
						exit(1);
					}
					free(var->temp);
					free(var->cmd_path);
					var->temp = NULL;
					var->cmd_path = NULL;
				}
			}
			else
			{
				if (access(cmd[0]->cmd[0], F_OK) == -1)
				{
					printf("command not found !!!\n");
					exit(1);
				}
				else
					var->cmd_path = cmd[0]->cmd[0];
			}
			if (execve(var->cmd_path, cmd[0]->cmd, input->env) == -1)
				printf("execve failed!!!\n");
			exit(0);
		}
	}
	else
		execute_pipes(cmd, input, var);
	return (true);
}

int main (int ac, char **av, char **env)
{
	t_input	input;
	t_var	var;
	t_cmd	**cmd;

	(void)av;
	(void)ac;
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		input.num_of_cmd = 1;
		input.cmds = readline("\x1b[94mMinishell >> \x1b[0m");
		input.env = env;
		if (!input.cmds)
		{
			free_all(NULL, &input, &var);
			clear_history();
			exit(1);
		}
		add_history(input.cmds);
		if (parsing(&input))
		{
			cmd = (t_cmd **)ft_calloc(input.num_of_cmd, sizeof(t_cmd));
			cmd[input.num_of_cmd] = NULL;
			tokenize_cmds(&input, cmd, &var);
			if (cmd)
			{
				if (execute(cmd, &input, &var))
					free_all(cmd, &input, &var);
			}
			else
				continue ;
		}
		continue ;
	}
	return (0);
}
