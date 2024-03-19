/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:01:06 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/19 20:24:21 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_c(char const *s, char c, t_var *var)
{
	while (s[var->i])
	{
		while (s[var->i] && s[var->i] == c)
			var->i++;
		if (s[var->i] == '"' || s[var->i] == '\'')
		{
			var->j = s[var->i++];
			if (!(s[var->i] == var->j))
			{
				var->c++;
				while (s[var->i] && s[var->i] != var->j)
					var->i++;
			}
			var->i++;
		}
		else if (s[var->i] && s[var->i] != c)
		{
			var->c++;
			while (s[var->i] && s[var->i] != c
				&& !(s[var->i] == '"' || s[var->i] == '\''))
				var->i++;
		}
	}
}

static	int	ft_end(char const *s, char c, int start)
{
	char	k;

	while (s[start] && s[start] == c)
		start++;
	if (s[start] == '"' || s[start] == '\'')
	{
		k = s[start++];
		while (s[start] && s[start] != k)
			start++;
		return (start);
	}
	if (s[start] && s[start] != c && s[start] != '"' && s[start] != '\'')
	{
		while (s[start] && s[start] != c && s[start] != '"' && s[start] != '\'')
			start++;
		return (start);
	}
	return (start);
}

static	char	**ft_free(char **d, int l)
{
	while (l >= 0)
	{
		free(d[l]);
		l--;
	}
	free(d);
	return (0);
}

static	char	**ft_set(char const *s, char **d, char c, int cc)
{
	t_var	var;

	var.c = 0;
	var.n = 0;
	var.i = 0;
	var.len = ft_strlen(s);
	while (var.c < cc && var.i <= var.len)
	{
		while (s[var.i] && s[var.i] == c)
			var.i++;
		while (s[var.i] && s[var.i++] && (s[var.i] == '"' || s[var.i] == '\'') && (s[var.i + 1] == '"' || s[var.i + 1] == '\''))
			var.i += 2;
		var.j = ft_end(s, c, var.i++);
		d[var.c] = malloc(sizeof(char) * (var.j - var.i + 2));
		if (!d[var.c])
			return (ft_free(d, var.c));
		var.n = 0;
		while (var.i <= var.j && var.i <= var.len)
		{
			if (s[var.i] == '"' || s[var.i] == '\'')
				var.i++;
			else
				d[var.c][var.n++] = s[var.i++];
		}
		d[var.c][var.n] = 0;
		var.c++;
	}
	return (d);
}

char	**mini_split(char const *s, char c)
{
	char	**d;
	t_var	var;

	var.i = 0;
	var.c = 0;
	if (!s)
		return (NULL);
	ft_c(s, c, &var);
	d = malloc(sizeof(char *) * (var.c + 1));
	if (!d)
		return (NULL);
	d = ft_set(s, d, c, var.c);
	if (d)
	{
		d[var.c] = NULL;
		return (d);
	}
	return (NULL);
}
