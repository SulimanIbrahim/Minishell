/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:01:06 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/03/24 05:42:53 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_word_counter(char *s, char c, t_var *var)
{
	while (s[var->i])
	{
		var->i += skip(s + var->i, ' ');
		if (s[var->i] == '"' || s[var->i] == '\'')
		{
			var->j = s[var->i++];
			var->i += skip(s + var->i, ' ');
			if (!(s[var->i] == var->j))
			{
				var->closed++;
				while (s[var->i] && s[var->i] != var->j)
					var->i++;
			}
			else
				var->i++;
		}
		if (s[var->i] && s[var->i] != c)
		{
			var->closed++;
			while (s[var->i] && s[var->i] != c)
				var->i++;
		}
	}
}

static	int	ft_end(char *s, char c, int start)
{
	char	k;

	while (s[start])
	{
		start += skip(s + start, ' ');
		if (s[start] && (s[start] == '"' || s[start] == '\''))
		{
			k = s[start++];
			start += skip(s + start, ' ');
			while (s[start] && s[start] != k)
				start++;
		}
		while (s[start] && s[start] != c && s[start] != '"' && s[start] != '\'')
			start++;
		if (s[start] && s[start] == c)
			return (start - 1);
	}
	return (start);
}

static	int	ft_check_qout(t_var *var)
{
	char	k;
	int		i;

	i = var->i;
	i += skip(var->temp + i, ' ');
	while (var->temp[i] && (var->temp[i] == '"' || var->temp[i] == '\''))
	{
		k = var->temp[i++];
		i += skip(var->temp + i, ' ');
		if (var->temp[i] == k)
			return (++i);
	}
	return (0);
}

static	char	**ft_set(char **d, char c, int cc, t_var *var)
{
	while (var->c < cc && var->i <= var->len)
	{
		var->i += skip(var->temp + var->i, ' ');
		while (!(ft_check_qout(var) == 0))
			var->i = ft_check_qout(var);
		var->i += skip(var->temp + var->i, ' ');
		var->j = ft_end(var->temp, c, var->i);
		d[var->c] = malloc((var->j - var->i + 2));
		if (!d[var->c])
			return (NULL);
		var->n = 0;
		while (var->i <= var->j && var->i <= var->len)
		{
			if (var->temp[var->i] != '"' && var->temp[var->i] != '\'')
				d[var->c][var->n++] = var->temp[var->i];
			var->i++;
		}
		d[var->c][var->n] = 0;
		var->c++;
	}
	return (d);
}

char	**mini_split(char *s, char c)
{
	char	**d;
	t_var	var;

	var.i = 0;
	var.c = 0;
	var.n = 0;
	var.closed = 0;
	var.len = ft_strlen(s);
	if (!s)
		return (NULL);
	ft_word_counter(s, c, &var);
	d = malloc(sizeof(char *) * (var.closed + 1));
	if (!d)
		return (NULL);
	var.temp = s;
	var.i = 0;
	d = ft_set(d, c, var.closed, &var);
	if (d)
	{
		d[var.c] = NULL;
		return (d);
	}
	return (NULL);
}
