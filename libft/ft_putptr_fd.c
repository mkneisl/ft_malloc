/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:24:05 by mkneisl           #+#    #+#             */
/*   Updated: 2025/03/13 17:03:40 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include <stdint.h>

static unsigned int	digit_count(uint64_t n)
{
	if (n == 0)
		return (1);
	if (n / 16 == 0)
		return (1);
	return (1 + digit_count(n / 16));
}

static int	get_digit(uint64_t num, unsigned int digit)
{
	unsigned int	count;

	count = 0;
	while (count < digit - 1)
	{
		num /= 16;
		count++;
	}
	return (num % 16);
}

void	ft_putptr_fd(void* n, int fd)
{
	unsigned int	digitcount;
	unsigned int	cdigit;
	uint64_t	    num;
	char			c;
    int             digit;
    char            number[17];
	
    num = (uint64_t)n;
    ft_bzero(number, 17);
	digitcount = digit_count(num);
    cdigit = digitcount;
	while (cdigit > 0)
	{
        digit = get_digit(num, cdigit);
        if (digit < 10)
		    c = digit + 48;
		else
            c = digit + 55;
        number[digitcount -  cdigit] = c;
		cdigit--;
	}
    write(fd, number, digitcount);
}
