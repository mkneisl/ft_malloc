/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:48:33 by mkneisl           #+#    #+#             */
/*   Updated: 2022/04/25 22:41:40 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy( void *dest, const void *src, size_t size )
{
	size_t	bytescopied;

	if (!dest && !src)
		return (0);
	bytescopied = 0;
	while (bytescopied < size)
	{
		*((unsigned char *)dest + bytescopied)
			= *((unsigned char *)src + bytescopied);
		bytescopied++;
	}
	return (dest);
}
