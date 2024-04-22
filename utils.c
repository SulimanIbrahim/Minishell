/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:02:41 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/22 21:59:35 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	exit_atoi(const char *str)
{
	int					sign;
	unsigned char		res;
	unsigned long long	max;

	res = 0;
	sign = 1;
	max = 9223372036854775807;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (res > max && sign == 1)
			return (-1);
		if (res > max + 1 && sign == -1)
			return (0);
		str++;
	}
	return (res * sign);
}
