/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:20:43 by mkneisl           #+#    #+#             */
/*   Updated: 2022/03/24 13:54:16 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum( int arg )
{
	if (arg > 47 && arg < 58)
		return (1);
	if (arg > 64 && arg < 91)
		return (1);
	if (arg > 96 && arg < 123)
		return (1);
	return (0);
}
