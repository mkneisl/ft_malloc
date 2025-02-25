/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_sb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 22:00:38 by mkneisl           #+#    #+#             */
/*   Updated: 2022/08/01 15:49:08 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	digit_count(long long n, int base)
{
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	if (n / base == 0)
		return (1);
	return (1 + digit_count(n / base, base));
}

static void	swap_num(char *str, unsigned int *cursor
, unsigned long long *n, int base)
{
	while (*n > 0)
	{
		if (*(long long *)n % base < 10)
			str[*cursor] = (char)((*(long long *)n % base) + 48);
		else
			str[*cursor] = (char)((*(long long *)n % base) + 87);
		*n /= base;
		*cursor -= 1;
	}
}

char	*ft_itoa_sb(long long num, int base)
{
	char				*str;
	unsigned long long	n;
	unsigned int		cursor;
	unsigned int		dcount;

	if (num < 0)
		n = (num * -1);
	else
		n = num;
	dcount = (digit_count(n, base) + 1);
	if (num < 0 && base == 10)
		dcount++;
	cursor = dcount - 2;
	str = malloc(dcount);
	if (!str)
		return (0);
	if (num < 0)
		*str = 45;
	swap_num(str, &cursor, &n, base);
	if (cursor == (dcount - 2))
		str[cursor] = 48;
	str[dcount - 1] = 0;
	return (str);
}
