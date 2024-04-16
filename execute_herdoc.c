/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_herdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:35:28 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/16 14:36:51 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_herdoc_fd(t_red *p)
{
	while (p)
	{
		if (p->input_herdoc_fd != -1)
		{
			printf("%d\n", p->input_herdoc_fd);
			close(p->input_herdoc_fd);
		}
		p = p->next_redricts;
	}
}

void	set_herdoc(t_red *p)
{
	char	*tmp;

	while (p)
	{
		if (p->type == HERDOC)
		{
			unlink("tmp");
			p->input_herdoc_fd = open("tmp", O_CREAT | O_RDWR, 0777);
			ft_putstr_fd("> ", STDOUT_FILENO);
			tmp = get_next_line(STDIN_FILENO);
			while (tmp && !(ft_strlen(p->file_name) == ft_strlen(tmp) - 1
					&& !ft_strncmp(p->file_name, tmp, ft_strlen(p->file_name))))
			{
				ft_putstr_fd("> ", STDOUT_FILENO);
				ft_putstr_fd(tmp, p->input_herdoc_fd);
				free(tmp);
				tmp = get_next_line(STDIN_FILENO);
			}
			if (tmp)
				free(tmp);
			close(p->input_herdoc_fd);
			p->input_herdoc_fd = open("tmp", O_RDONLY | O_CREAT, 0777);
		}
		p = p->next_redricts;
	}
}
