#include "minishell.h"

int cd(char *s)
{
	int i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (!s || !s[i])
		chdir("HOME");
	else
		chdir(s + i);
	return (1);
}

int	pwd(void)
{
	return (printf("%s\n", getenv("PWD")));
}

int	echo(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] && s[i] == '-' && s[i + 1] == 'n')
	{
		i += 2;
		while (s[i] && s[i] == ' ')
			i++;
		flag = 1;
	}
	while (s[i])
	{
		if (s[i] != '"' && s[i] != '\'')
			write(1, &s[i],1);
		i++;
	}
	if (flag == 0)
		write(1, "\n",1);
	return (1);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		echo(env[i++]);
	return (1);
}

bool	ft_exec_builtin(char *s, int i, t_input *input)
{
	printf("inside!!!!!!!!!!!!!!!!!!!\n");
	if (i == 0)
		return (cd(s));
	else if (i == 1)
		return (echo(s));
	else if (i == 2)
		return (pwd());
	else if (i == 3)
		export(s, input);
	else if (i == 4)
		return (1);
	else if (i == 5)
		return (ft_env(input->env));
	return (true);
}

bool	ft_check_builtins(t_cmd *cmd, t_input *input)
{
	char *builtins[] = {"cd", "echo"
			, "pwd", "export", "unset", "env", NULL};
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (builtins[i])
	{
		if (builtins[i][j] == cmd->cmd_name[j])
		{
			while (cmd->cmd_name[j] && builtins[i][j]
					&& cmd->cmd_name[j] != ' '
					&& cmd->cmd_name[j] == builtins[i][j])
				j++;
			if (!builtins[i][j] && (!cmd->cmd_name[j] || cmd->cmd_name[j] == ' '))
				return (ft_exec_builtin(cmd->cmd_name + j, i, input));
		}
		j = 0;
		i++;
	}
	return (false);
}
