/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:36:16 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/13 14:46:52 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	myfree(char **ptr)
{
	int	cursor;

	cursor = -1;
	while (ptr[++cursor])
		free(ptr[cursor]);
	free(ptr);
	return ;
}

static int	get_strcount(char const *s, char c)
{
	unsigned int	cursor;
	int				count;

	cursor = 0;
	count = 0;
	if (s[0] != c)
		count++;
	while (s[cursor + 1] != 0)
	{
		if (s[cursor] == c && s[cursor + 1] != c)
			count++;
		cursor++;
	}
	return (count);
}

static int	get_nstr(const char *s, unsigned int *start, unsigned int *length,
					char c)
{
	unsigned int	cursor;

	cursor = *start + *length;
	while (s[cursor] == c && s[cursor])
		cursor++;
	*start = cursor;
	*length = 0;
	while (s[cursor] != c && s[cursor])
	{
		*length = *length + 1;
		cursor++;
	}
	return (*length);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	start;
	unsigned int	length;
	unsigned int	strcount;
	char			**ret;

	if (!s)
		return (0);
	if (!*s)
		return (ft_calloc(8, 1));
	strcount = 0;
	start = 0;
	length = 0;
	ret = ft_calloc(get_strcount(s, c) + 1, sizeof(char *));
	if (!ret)
		return (0);
	while (get_nstr(s, &start, &length, c))
	{
		ret[strcount] = ft_substr(s, start, length);
		if (!ret[strcount++])
		{
			myfree(ret);
			return (0);
		}
	}
	return (ret);
}
