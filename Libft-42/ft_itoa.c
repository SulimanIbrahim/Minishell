/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:14:10 by suibrahi          #+#    #+#             */
/*   Updated: 2023/08/07 02:20:26 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countnum(int c)
{
	int	numdigit;

	numdigit = 0;
	while (c != 0)
	{
		c /= 10;
		numdigit++;
	}
	return (numdigit);
}

static char	*zero_case(void)
{
	char	*result;

	result = (char *)malloc(2 * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[0] = '0';
	result[1] = '\0';
	return (result);
}

static char	*min_int_case(void)
{
	char	*result;

	result = (char *)malloc(12 * sizeof(char));
	return (ft_memcpy(result, "-2147483648", 12));
}

static int	is_negative(int n)
{
	if (n < 0)
	{
		return (1);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	int		isnegative;
	char	*str;
	int		i;

	if (n == 0)
		return (zero_case());
	if (n == -2147483648)
		return (min_int_case());
	isnegative = is_negative(n);
	str = (char *)malloc((countnum(n) + isnegative + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = countnum(n) + isnegative;
	str[i] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (i-- > isnegative)
	{
		str[i] = '0' + (n % 10);
		n /= 10; 
	}
	return (str);
}
