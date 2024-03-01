/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:43:52 by suibrahi          #+#    #+#             */
/*   Updated: 2023/08/09 01:43:55 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	map_function(char c)
// {
// 	if (c >= 'a' && c <= 'z')
// 		return (c - 'a' + 'A');
// 	else
// 		return (c);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned
int, char))
{
	int		len;
	int		i;
	char	*result;

	i = 0;
	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
