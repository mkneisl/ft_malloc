/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:57:45 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/13 14:47:28 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_forbiddenc(const char *exclude, const char check)
{
	exclude--;
	while (*++exclude)
		if (*exclude == check)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	unsigned int	cursor;
	unsigned int	size;
	unsigned int	start;
	unsigned int	end;

	if (!str)
		return (0);
	cursor = 0;
	size = ft_strlen(str);
	while (is_forbiddenc(set, *(str + cursor)) && *(str + cursor))
		cursor++;
	if (cursor == size)
		return (ft_strdup(""));
	start = cursor;
	cursor = (size - 1);
	while (is_forbiddenc(set, *(str + cursor)) && cursor > 1)
		cursor--;
	end = cursor;
	return (ft_substr(str, start, (end - start + 1)));
}
