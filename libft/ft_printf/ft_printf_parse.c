/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 22:02:25 by mkneisl           #+#    #+#             */
/*   Updated: 2025/03/27 12:28:24 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fix_str(char *str)
{
	while (*str)
	{
		if (*(unsigned char *)str == (unsigned char)255)
			*str = 0;
		str++;
	}
}

int	is_cmd(char c)
{
	if (c == 'c' || c == 's')
		return (1);
	else if (c == 'p' || c == 'i'
		|| c == 'u' || c == 'x'
		|| c == 'X' || c == 'd'
		|| c == 'l')
		return (2);
	else if (c == '-' || c == '+'
		|| c == ' ' || c == '#'
		|| c == '0')
		return (5);
	else if (ft_isdigit(c))
		return (4);
	else
		return (0);
}

int	parse_digit(char *command, int *idx)
{
	char	*adigits;
	int		index;

	index = 0;
	while (is_cmd(command[index]) == 4)
		index++;
	if (!index)
		return (-1);
	adigits = ft_substr(command, 0, index);
	*idx += index;
	index = ft_atoi(adigits);
	free(adigits);
	return (index);
}

void	parse_comand(char *command, t_prntf_arg* arg)
{
	int	index;

	index = 1;
	arg->flags = 0;
	arg->percision = -1;
	arg->conv_char = 0;
	while (is_cmd(command[index]) == 5)
		index++;
	if (index != 1)
		arg->flags = ft_substr(command, 1, index - 1);
	arg->min_width = parse_digit(command + index, &index);
	if (command[index] == '.')
	{
		index++;
		arg->percision = parse_digit(command + index, &index);
	}
	if (command[index] == 'l')
	{
		index++;
		arg->large = 1;
	}
	arg->type = is_cmd(command[index]);
	if (arg->type && arg->type < 3)
		arg->conv_char = command[index];
}
