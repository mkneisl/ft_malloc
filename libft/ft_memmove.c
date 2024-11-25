/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:09:06 by mkneisl           #+#    #+#             */
/*   Updated: 2022/04/25 22:45:06 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_overlap(unsigned long long ptr1, unsigned long long ptr2,
				size_t size)
{
	unsigned long long	end1;
	unsigned long long	end2;

	end1 = ptr1 + size;
	end2 = ptr2 + size;
	if (ptr2 > ptr1 && ptr2 < end1)
		return (-1);
	if (end2 > ptr1 && end2 < end1)
		return (1);
	return (1);
}

void	*ft_memmove( void *dest, const void *src, size_t size )
{
	int		cursor;
	int		dir_v;
	size_t	bytesmoved;

	if (!dest && !src)
		return (0);
	dir_v = get_overlap((unsigned long long)src,
			(unsigned long long)dest, size);
	if (dir_v == -1)
		cursor = size - 1;
	else
		cursor = 0;
	bytesmoved = 0;
	while (bytesmoved < size)
	{
		*((char *)(dest) + cursor) = *((char *)(src) + cursor);
		cursor += dir_v;
		bytesmoved++;
	}
	return (dest);
}
