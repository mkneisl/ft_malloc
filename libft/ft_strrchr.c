/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:34:22 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/07 17:34:51 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str_in, int c)
{
	char	*last_occurrence;
	char	*str;

	str = (char *)str_in;
	last_occurrence = 0;
	while (*str)
	{
		if (*(unsigned char *)str == (unsigned char)c)
			last_occurrence = str;
		str++;
	}
	if (*(unsigned char *)str == (unsigned char)c)
	{
		last_occurrence = str;
	}
	return ((char *)last_occurrence);
}
