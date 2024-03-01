/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:26:13 by suibrahi          #+#    #+#             */
/*   Updated: 2023/08/04 07:35:09 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *pattern, size_t len)
{
	size_t	ptnlen;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ptnlen = ft_strlen(pattern);
	if (ptnlen == 0)
		return ((char *)str);
	if (str == NULL && len == 0)
		return (NULL);
	while (str[j] != '\0')
	{
		i = 0;
		while (str[j + i] == pattern[i] && (j + i) < len)
		{
			while (str[j + i] == '\0' && pattern[i] == '\0')
				return ((char *)&str[j]);
			i++;
		}
		if (pattern[i] == '\0')
			return ((char *)str + j);
		j++;
	}
	return (NULL);
}
