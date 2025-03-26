/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:09:51 by mkneisl           #+#    #+#             */
/*   Updated: 2022/04/02 16:53:17 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *str, int c, size_t n)
{
	size_t	cursor;

	cursor = 0;
	while (cursor < n)
	{
		if (*(unsigned char *)str == (unsigned char)c)
			return (str);
		cursor++;
		str++;
	}
	return (0);
}
