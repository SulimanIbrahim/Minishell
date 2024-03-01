/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:04:56 by suibrahi          #+#    #+#             */
/*   Updated: 2023/08/07 03:54:57 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strings_count(char const *s, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			word_count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		start;
	char	**substr;
	int		word_count;

	if (s == NULL)
		return (0);
	word_count = strings_count(s, c);
	substr = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		substr[j++] = ft_substr(s, start, i - start);
	}
	substr[j] = NULL;
	return (substr);
}
int main()
{
	char *s = "thgfv yjghb yjfhgvn";
	char **result;
	result = ft_split(s,' ');

	int i = 0;
	while(result[i] != NULL)
	{
		printf("%s\n", result[i]);
		i++;
	}
}
