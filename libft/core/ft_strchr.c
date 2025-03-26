/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:27:24 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/07 17:33:04 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned int	cursor;

	cursor = 0;
	while (str[cursor])
	{
		if ((unsigned char)str[cursor] == (unsigned char)c)
			return ((char *)(str + cursor));
		cursor++;
	}
	if ((unsigned char)str[cursor] == (unsigned char)c)
		return ((char *)(str + cursor));
	return (0);
}
