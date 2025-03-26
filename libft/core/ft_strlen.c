/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:55:25 by mkneisl           #+#    #+#             */
/*   Updated: 2023/02/13 20:02:38 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen( const char *str )
{
	size_t	strsize;

	if (!str)
		return (0);
	strsize = 0;
	while (*str)
	{
		strsize++;
		str++;
	}
	return (strsize);
}
