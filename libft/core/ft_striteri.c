/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:52:17 by mkneisl           #+#    #+#             */
/*   Updated: 2022/05/12 20:43:44 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	cursor;

	if (!s)
		return ;
	cursor = 0;
	while (s[cursor])
	{
		f(cursor, (s + cursor));
		cursor++;
	}
	return ;
}
