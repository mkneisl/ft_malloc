/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:11:26 by mkneisl           #+#    #+#             */
/*   Updated: 2023/02/26 20:57:43 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char			*ptr;
	unsigned int	length;

	length = ft_strlen(str);
	ptr = (char *)ft_calloc(length + 1, 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, str, length);
	return (ptr);
}
