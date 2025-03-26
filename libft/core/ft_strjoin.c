/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:40:20 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/13 14:47:03 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	unsigned int	size1;
	unsigned int	size2;
	unsigned int	cursor;
	char			*str;

	str = 0;
	cursor = 0;
	if (!str1 || !str2)
		return (0);
	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	str = malloc(size1 + size2 + 1);
	if (!str)
		return (str);
	while (cursor < (size1 + size2))
	{
		if (cursor < size1)
			*(str + cursor) = *(str1 + cursor);
		else
			*(str + cursor) = *(str2 + (cursor - size1));
		cursor++;
	}
	str[size1 + size2] = 0;
	return (str);
}
