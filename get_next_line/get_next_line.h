/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:58:27 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/04 12:27:40 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../Libft-42/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7024
# endif

char	*get_next_line(int fd);
char	*ft_g_strdup(char *s, int k);
char	*ft_g_strjoin(char *s1, char *s2);

#endif