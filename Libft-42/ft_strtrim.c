/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:04:56 by suibrahi          #+#    #+#             */
/*   Updated: 2023/08/06 07:51:11 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		j;
	int		end;
	char	*trimmeds1;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		++start;
	end = ft_strlen(s1);
	if (start == end)
		return (ft_strdup(""));
	while (end >= 0 && ft_strchr(set, s1[end - 1]))
		--end;
	if (start > end)
		return (ft_strdup(""));
	trimmeds1 = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!trimmeds1)
		return (NULL);
	j = 0;
	while (start < end)
		trimmeds1[j++] = s1[start++];
	trimmeds1[j] = '\0';
	return (trimmeds1);
}
