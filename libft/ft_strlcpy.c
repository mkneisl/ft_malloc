/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:21:35 by mkneisl           #+#    #+#             */
/*   Updated: 2022/04/04 17:41:14 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	bytescopied;

	bytescopied = -1;
	if (!size)
		return (ft_strlen(src));
	while (++bytescopied < (size - 1))
	{
		if (src[bytescopied])
			dest[bytescopied] = src[bytescopied];
		else
			break ;
	}
	dest[bytescopied] = 0;
	return (ft_strlen(src));
}
