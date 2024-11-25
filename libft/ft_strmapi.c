/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:43:14 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/13 14:47:11 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	cursor;
	size_t			strleng;
	char			*ret;

	ret = 0;
	cursor = 0;
	if (!s || !f)
		return (0);
	strleng = ft_strlen(s);
	ret = (char *)malloc(strleng + 1);
	if (!ret)
		return (ret);
	while (cursor < strleng)
	{
		*(ret + cursor) = f(cursor, *(s + cursor));
		cursor++;
	}
	ret[strleng] = 0;
	return (ret);
}
