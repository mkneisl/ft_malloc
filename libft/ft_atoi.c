/* ************************************************************************** */
/*                                                                           */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:03:47 by mkneisl           #+#    #+#             */
/*   Updated: 2022/03/25 18:12:05 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == 0x20 || c == 0x9)
		return (1);
	if (c == 0xa || c == 0xb)
		return (1);
	if (c == 0xc || c == 0xd)
		return (1);
	return (0);
}

static const char	*discard_space(const char *str, int *is_negative)
{
	unsigned int	cursor;

	cursor = 0;
	while (ft_isspace(str[cursor]))
		cursor++;
	if (str[cursor] == '-')
	{
		*is_negative = 1;
		cursor++;
	}
	else if (str[cursor] == '+')
	{
		*is_negative = 0;
		cursor++;
	}
	else
	{
		*is_negative = 0;
	}
	return (str + cursor);
}

int	ft_atoi(const char *str)
{
	int				cursor;
	unsigned int	parsed_int;
	int				negative;

	cursor = 0;
	parsed_int = 0;
	negative = 0;
	str = discard_space(str, &negative);
	while (ft_isdigit(str[cursor]))
	{
		parsed_int += (str[cursor] - 48);
		if (ft_isdigit(str[cursor + 1]))
			parsed_int *= 10;
		cursor++;
	}
	if (negative)
		return ((int)(parsed_int *= -1));
	else
		return ((int)parsed_int);
}
