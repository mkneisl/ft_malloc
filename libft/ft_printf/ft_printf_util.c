/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:02:59 by mkneisl           #+#    #+#             */
/*   Updated: 2022/07/02 19:02:59 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conv_to_upper(char *str)
{
	int	cursor;

	cursor = -1;
	while (str[++cursor])
		str[cursor] = ft_toupper(str[cursor]);
}

char	*apply_min_width(char *str, char filler, int bound, int minw)
{
	char	*ret;
	int		strwidth;

	ret = 0;
	strwidth = ft_strlen(str);
	if (strwidth >= minw)
		return (str);
	ret = ft_calloc(minw + 1, 1);
	if (!ret)
		return (NULL);
	ft_memset(ret, (int)filler, minw);
	if (!bound)
		ft_strlcpy(ret, str, strwidth);
	else
		ft_memcpy(ret + (minw - strwidth), str, strwidth);
	free(str);
	return (ret);
}

char	*process_number_arg(t_prntf_arg cmd, va_list *vlst)
{
	char	*ret;

	ret = 0;
	if (cmd.conv_char == 'd' || cmd.conv_char == 'i')
		ret = ft_itoa(va_arg(*vlst, int));
	if (cmd.conv_char == 'u')
		ret = ft_itoa_ub((unsigned long long)va_arg(*vlst, unsigned int), 10);
	if (cmd.conv_char == 'x')
		ret = ft_itoa_ub((unsigned long long)va_arg(*vlst, unsigned int), 16);
	if (cmd.conv_char == 'X')
	{
		ret = ft_itoa_ub((unsigned long long)va_arg(*vlst, unsigned int), 16);
		conv_to_upper(ret);
	}
	if (cmd.conv_char == 'p')
	{
		ret = ft_itoa_ub(va_arg(*vlst, unsigned long long), 16);
		ret = append(ft_strdup("0x"), ret);
	}
	return ((ret));
}

char	*process_char_arg(t_prntf_arg cmd, va_list *vlst)
{
	char	*ret;

	ret = 0;
	if (cmd.conv_char == 'c')
	{
		ret = malloc(2);
		ret[0] = va_arg(*vlst, int);
		if (!ret[0])
			ret[0] = (unsigned char)255;
		ret[1] = 0;
	}
	else if (cmd.conv_char == 's')
	{
		ret = va_arg(*vlst, char *);
		if (!ret)
			ret = ft_strdup("(null)");
		else
			ret = ft_strdup(ret);
	}
	return (ret);
}
