/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:14:07 by mkneisl           #+#    #+#             */
/*   Updated: 2022/08/04 00:27:03 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*append(char *str, char *to_append)
{
	size_t	origl;
	size_t	newlen;
	char	*ret;

	if (!to_append)
	{
		if (str)
			free(str);
		return (0);
	}
	if (str)
		origl = ft_strlen(str);
	else
		origl = 0;
	newlen = ft_strlen(to_append) + origl;
	if (newlen == origl)
		newlen++;
	ret = ft_calloc(newlen + 1, 1);
	if (str)
		ft_memcpy(ret, str, origl);
	ft_strlcat(ret, to_append, newlen + 1);
	free(str);
	free(to_append);
	return (ret);
}

static int	get_next_part(const char *s, unsigned int *start
, unsigned int *length)
{
	unsigned int	cursor;

	cursor = *start + *length;
	*start = cursor;
	*length = 0;
	if (s[cursor] != '%')
	{
		while (s[cursor] && s[cursor] != '%')
		{
			*length = *length + 1;
			cursor++;
		}
		return (*length);
	}
	if (s[++cursor] == '%')
		return (*length = *length + 2);
	if (is_cmd(s[cursor]) == 2 || is_cmd(s[cursor]) == 1)
		cursor++;
	*length = cursor - *start;
	return (*length);
}

char	*process_str(char *str, va_list *vlst, unsigned int *length)
{
	char		*ret;
	t_prntf_arg	cmd;

	if (!str || *str != '%')
	{
		*length += ft_strlen(str);
		return (str);
	}
	if (*str == '%' && *(str + 1) == '%')
	{
		*length += 1;
		free(str);
		return (ft_strdup("%"));
	}
	cmd = parse_comand(str);
	if (cmd.type == 1)
		ret = process_char_arg(cmd, vlst);
	else if (cmd.type == 2)
		ret = process_number_arg(cmd, vlst);
	else
		ret = 0;
	*length += ft_strlen(ret);
	free(str);
	return (ret);
}

int	ft_printf(const char *fmt, ...)
{
	va_list			vlst;
	unsigned int	start;
	unsigned int	len;
	unsigned int	length;
	char			*outstr;

	outstr = 0;
	start = 0;
	len = 0;
	length = 0;
	if (!*fmt)
		return (0);
	va_start(vlst, fmt);
	while (get_next_part(fmt, &start, &len))
	{
		outstr = append(outstr, process_str(ft_substr(fmt, start, len),
					&vlst, &length));
		if (!outstr)
			return (0);
	}
	va_end(vlst);
	fix_str(outstr);
	len = write(1, outstr, length);
	free(outstr);
	return ((int)len);
}
