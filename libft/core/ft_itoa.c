/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:10:53 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/13 14:45:37 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	digit_count(int n)
{
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	if (n / 10 == 0)
		return (1);
	return (1 + digit_count(n / 10));
}

static void	swap_num(char *str, unsigned int *cursor, unsigned int *n)
{
	while (*n > 0)
	{
		str[*cursor] = ((*n % 10) + 48);
		*n /= 10;
		*cursor -= 1;
	}
}

char	*ft_itoa(int num)
{
	char			*str;
	unsigned int	n;
	unsigned int	cursor;
	unsigned int	dcount;

	dcount = (digit_count(num) + 1);
	if (num < 0)
		dcount++;
	cursor = dcount - 2;
	str = malloc(dcount);
	if (!str)
		return (0);
	if (num < 0)
	{
		*str = 45;
		n = num * -1;
	}
	else
		n = num;
	swap_num(str, &cursor, &n);
	if (cursor == (dcount - 2))
		str[cursor] = 48;
	str[dcount - 1] = 0;
	return (str);
}
