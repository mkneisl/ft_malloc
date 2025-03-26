/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:56:50 by mkneisl           #+#    #+#             */
/*   Updated: 2023/02/25 20:30:53 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;
	size_t	counter;

	if (!num || !size)
		return (NULL);
	counter = 0;
	if (18446744073709551615UL / size < num)
		return (NULL);
	ptr = malloc(num * size);
	if (!ptr)
		return (ptr);
	while (counter < (num * size))
	{
		*(char *)(ptr + counter) = 0;
		counter++;
	}
	return (ptr);
}
