/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 07:11:04 by ahibrahi          #+#    #+#             */
/*   Updated: 2023/09/12 20:35:42 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_pset(int fd, const char type, va_list(args))
{
	int		c;

	c = 0;
	if (type == 'i' || type == 'd')
		c = ft_putnbr(fd, va_arg(args, int));
	else if (type == 'u')
		c = ft_u(fd, va_arg(args, unsigned int));
	else if (type == 'c')
		c = ft_putchar(fd, va_arg(args, int));
	else if (type == 's')
		c = ft_putstr(fd, va_arg(args, char *));
	else if (type == 'p')
		c = ft_p(fd, va_arg(args, unsigned long long));
	else if (type == 'x')
		c += ft_hex(fd, va_arg(args, unsigned int));
	else if (type == 'X')
		c += ft_hexb(fd, va_arg(args, unsigned int));
	else if (type == '%')
		c += write (1, "%", 1);
	return (c);
}

int	ft_printf(int fd, const char *type, ...)
{
	va_list	args;
	int		i;
	int		c;

	c = 0;
	i = 0;
	if (!type)
		return (0);
	va_start (args, type);
	{
		while (type[i])
		{
			if (type[i] == '%')
			{
				i++;
				c += ft_pset(fd, type[i], args);
			}
			else
				c += write (fd, &type[i], 1);
			i++;
		}
	}
	va_end (args);
	return (c);
}
