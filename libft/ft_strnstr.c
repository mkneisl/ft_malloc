/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:32:07 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/13 14:47:22 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*search, const char *to_search, size_t size)
{
	unsigned int	c1;
	size_t			smalllen;

	c1 = 0;
	smalllen = ft_strlen(to_search);
	if (smalllen < 1 || search == to_search)
		return ((char *) search);
	while (c1 < size && search[c1])
	{
		if (search[c1] == to_search[0] && (c1 + smalllen) <= size)
		{
			if (ft_strncmp((search + c1), to_search, smalllen) == 0)
				return ((char *)(search + c1));
		}
		c1++;
	}
	return (0);
}
