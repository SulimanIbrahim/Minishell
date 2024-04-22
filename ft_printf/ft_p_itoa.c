/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:27:48 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/01/25 16:43:54 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_counting(long long n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static	char	*ft_set(char *s, long long n, int len)
{
	long long	c;
	long long	l;

	l = 10;
	if (n < 0)
	{
		s[0] = '-';
		n = n * -1;
	}
	len--;
	if (n > 0)
		s[len] = (n % 10) + 48;
	len--;
	while (n >= l)
	{
		l *= 10;
		c = (n % l);
		s[len] = c / (l / 10) + 48;
		len--;
	}
	return (s);
}

int	ft_p_itoa(int fd, long long n)
{
	char	*s;
	int		len;

	if (n == 0)
		return (ft_putstr(fd, "0"));
	if (n == -2147483648)
		return (ft_putstr(fd, "-2147483648"));
	len = ft_counting(n);
	if (n != 0)
	{
		s = malloc(len + 1);
		if (!s)
			return (0);
		s = ft_set(s, n, len);
		s[len] = 0;
		ft_putstr(fd, s);
		free(s);
		return (len);
	}
	return (0);
}
