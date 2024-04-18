/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 05:45:43 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/18 14:10:12 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_path(char **env)
{
	if (!env)
		return (NULL);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0 && (*env)[4] == '=')
			return (*env + 5);
		env++;
	}
	return (NULL);
}
