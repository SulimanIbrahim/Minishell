/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 04:13:37 by suibrahi          #+#    #+#             */
/*   Updated: 2023/08/06 04:19:43 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*str;
	t_list	*temp;

	if (!lst || !del)
		return ;
	str = *lst;
	while (str)
	{
		temp = str->next;
		ft_lstdelone(str, del);
		str = temp;
	}
	*lst = NULL;
}
