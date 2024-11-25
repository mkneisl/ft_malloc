/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:34:27 by mkneisl           #+#    #+#             */
/*   Updated: 2022/04/02 16:50:08 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset( void *ptr, int value, size_t size )
{
	size_t	copiedbytes;

	copiedbytes = 0;
	while (copiedbytes < size)
	{
		*((unsigned char *)ptr + copiedbytes) = (unsigned char)value;
		copiedbytes++;
	}
	return (ptr);
}
