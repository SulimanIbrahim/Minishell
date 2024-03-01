/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:22:17 by suibrahi          #+#    #+#             */
/*   Updated: 2023/08/07 02:15:23 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
	{
		ptr = malloc(1);
		if (ptr)
			ft_bzero(ptr, 1);
		return (ptr);
	}
	if ((int)count < 0 || (int)size < 0 || size * count >= SIZE_MAX || 
		size * count >= 2147483647)
		return (NULL);
	ptr = malloc(size * count);
	if (!ptr)
	{
		free (ptr);
		return (NULL);
	}
	ft_bzero(ptr, size * count);
	return (ptr);
}
