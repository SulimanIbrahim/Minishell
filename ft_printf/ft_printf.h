/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 07:13:36 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/02/06 05:51:11 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(int fd, const char *type, ...);
int		ft_putchar(int fd, char c);
int		ft_putstr(int fd, char *s);
int		ft_putnbr(int fd, int n);
int		ft_u(int fd, unsigned int n);
int		ft_p_itoa(int fd, long long n);
int		ft_p(int fd, unsigned long long p);
int		ft_hex(int fd, unsigned int x);
int		ft_hexb(int fd, unsigned int x);

#endif
