/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:01:42 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/01/25 16:42:24 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_count(int n)
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

static	void	ft_set(int fd, int n, int len)
{
	int		c;
	int		l;
	int		k;

	l = 0;
	k = 1;
	while (len-- > 1)
		k = k * 10;
	l = n / k;
	while (k > 0)
	{
		l = n / k;
		if (n > 10)
			c = (l % k) + 48;
		else
			c = l + 48;
		write(fd, &c, 1);
		n %= k;
		k /= 10;
		l = c - 48;
		c = 0;
	}
	return ;
}

int	ft_putnbr(int fd, int n)
{
	int		len;
	int		k;

	k = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
		k = 1;
	}
	len = ft_count(n);
	if (n == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	if (n == -2147483648)
	{
		write(fd, "2147483648", 10);
		return (11);
	}
	if (n > 0)
		ft_set(fd, n, len);
	return (len + k);
}
