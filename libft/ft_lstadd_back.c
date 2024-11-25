/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:48:55 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/13 14:45:34 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*endlist;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	endlist = ft_lstlast(*lst);
	if (!endlist)
		return ;
	endlist->next = new;
}
