/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:26:13 by suibrahi          #+#    #+#             */
/*   Updated: 2023/08/04 07:56:10 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			len;
	unsigned char	*str_1; 
	unsigned char	*str_2;

	str_1 = (unsigned char *)str1;
	str_2 = (unsigned char *)str2;
	len = 0;
	while (len < n)
	{
		if (str_1[len] != str_2[len])
		{
			return (str_1[len] - str_2[len]);
		}
		len++;
	}
	return (0);
}
