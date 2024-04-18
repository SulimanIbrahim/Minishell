/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_herdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:35:28 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/19 02:28:11 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_herdoc_fd(t_red *p)
{
	while (p)
	{
		if (p->input_herdoc_fd != -1)
			close(p->input_herdoc_fd);
		p = p->next_redricts;
	}
}

void	set_herdoc(t_red *p, t_input *input)
{
	char	*str;

	while (p)
	{
		if (p->type == HERDOC)
		{
			unlink("tmp");
			p->input_herdoc_fd = open("tmp", O_CREAT | O_RDWR, 0777);
			ft_putstr_fd("> ", STDOUT_FILENO);
			str = get_next_line(STDIN_FILENO);
			while (str && !(ft_strlen(p->file_name) == ft_strlen(str) - 1
					&& !ft_strncmp(p->file_name, str, ft_strlen(p->file_name))))
			{
				str = expand_herdoc(str, input);
				ft_putstr_fd("> ", STDOUT_FILENO);
				(ft_putstr_fd(str, p->input_herdoc_fd), free(str));
				str = get_next_line(STDIN_FILENO);
			}
			if (str)
				free(str);
			close(p->input_herdoc_fd);
			p->input_herdoc_fd = open("tmp", O_RDONLY, 0777);
		}
		p = p->next_redricts;
	}
}
