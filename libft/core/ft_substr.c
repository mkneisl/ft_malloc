/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:28:35 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/13 14:47:47 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	cursor;
	size_t	strl;
	char	*sub_str;

	sub_str = 0;
	cursor = start;
	if (!str)
		return (0);
	strl = ft_strlen(str);
	if (start > strl)
		return (ft_strdup(""));
	if (len > (strl - start))
		len = strl - start;
	sub_str = malloc(len + 1);
	if (!sub_str)
		return (sub_str);
	while (cursor < (start + len))
	{
		*(sub_str + (cursor - start)) = *(str + cursor);
		cursor++;
	}
	sub_str[len] = 0;
	return (sub_str);
}
