/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:52:02 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/13 21:58:36 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*nxt;

	if (!lst)
		return ;
	nxt = *lst;
	*lst = 0;
	while (nxt)
	{
		tmp = nxt;
		nxt = tmp->next;
		if (del)
			del(tmp->content);
		free(tmp);
	}
}
