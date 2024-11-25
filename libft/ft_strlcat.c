/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:07:33 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/07 17:03:21 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	cursor;
	size_t			src_size;
	size_t			dst_str_size;

	dst_str_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	if (!size)
		return (src_size);
	if (dst_str_size > size)
		return (size + src_size);
	if (src_size < 1)
		return (dst_str_size + src_size);
	cursor = dst_str_size;
	while (src[cursor - dst_str_size])
	{
		if (cursor < (size - 1))
			dest[cursor] = src[cursor - dst_str_size];
		else
			break ;
		cursor++;
	}
	dest[cursor] = 0;
	return (dst_str_size + src_size);
}
