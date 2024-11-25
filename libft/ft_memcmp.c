/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:25:53 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/13 14:46:12 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t	cursor;

	cursor = 0;
	while (cursor < num)
	{
		if (*(char *)(ptr1 + cursor) != *(char *)(ptr2 + cursor))
			return (*(unsigned char *)(ptr1 + cursor) -
				*(unsigned char *)(ptr2 + cursor));
		cursor++;
	}
	return (0);
}
