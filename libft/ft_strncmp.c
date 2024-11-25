/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:33:05 by mkneisl           #+#    #+#             */
/*   Updated: 2023/02/13 20:28:28 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t to_compare)
{
	unsigned int	cursor;

	if (!str1 || !str2)
		return (-1);
	cursor = 0;
	while (cursor < to_compare)
	{
		if ((unsigned char)str1[cursor] != (unsigned char)str2[cursor]
			|| !str1[cursor])
			return ((unsigned char)str1[cursor] - (unsigned char)str2[cursor]);
		cursor++;
	}
	return (0);
}
