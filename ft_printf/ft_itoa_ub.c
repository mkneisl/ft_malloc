/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 22:01:49 by mkneisl           #+#    #+#             */
/*   Updated: 2022/08/01 15:49:02 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	digit_count(unsigned long long n, int base)
{
	if (n == 0x0)
		return (1);
	if (n / base == 0x0)
		return (1);
	return (1 + digit_count((unsigned long long)(n / base), base));
}

static void	swap_num(char *str, unsigned int *cursor,
			unsigned long long *n, int base)
{
	int	val;

	while (*n > 0)
	{
		val = *n % base;
		if (val < 10)
			str[*cursor] = (char)(val + 48);
		else
			str[*cursor] = (char)(val + 87);
		*n /= base;
		*cursor -= 1;
	}
}

char	*ft_itoa_ub(unsigned long long num, int base)
{
	char				*str;
	unsigned long long	n;
	unsigned int		cursor;
	unsigned int		dcount;

	n = num;
	dcount = (digit_count(n, base) + 1);
	if (*(long long *)&num < 0 && base == 10)
		dcount++;
	cursor = dcount - 2;
	str = malloc(dcount);
	if (!str)
		return (0);
	if (*(long long *)&num < 0)
		*str = 45;
	swap_num(str, &cursor, &n, base);
	if (cursor == (dcount - 2))
		str[cursor] = 48;
	str[dcount - 1] = 0;
	return (str);
}
