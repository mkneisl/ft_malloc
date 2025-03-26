/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:02:41 by mkneisl           #+#    #+#             */
/*   Updated: 2022/11/28 21:03:48 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	digit_count(unsigned int n)
{
	if (n == 0)
		return (1);
	if (n / 10 == 0)
		return (1);
	return (1 + digit_count(n / 10));
}

static int	get_digit(unsigned int num, unsigned int digit)
{
	unsigned int	count;

	count = 0;
	while (count < digit - 1)
	{
		num /= 10;
		count++;
	}
	return (num % 10);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	digitcount;
	unsigned int	num;
	char			c;

	if (n < 0)
	{
		write(fd, "-", 1);
		num = n * -1;
	}
	else
		num = n;
	digitcount = digit_count(num);
	while (digitcount > 0)
	{
		c = (get_digit(num, digitcount) + 48);
		write(fd, &c, fd);
		digitcount--;
	}
}
