/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:41:51 by mkneisl           #+#    #+#             */
/*   Updated: 2022/04/02 16:50:35 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t size)
{
	size_t	byteszeroed;

	byteszeroed = 0;
	while (byteszeroed < size)
	{
		*((char *)ptr + byteszeroed) = (char)0;
		byteszeroed++;
	}
}
