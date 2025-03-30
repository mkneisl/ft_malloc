/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:29:49 by mkneisl           #+#    #+#             */
/*   Updated: 2025/03/27 12:24:30 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <unistd.h>
# include <stdarg.h>

typedef struct s_prntf_arg
{
	char	*flags;
	int		min_width;
	int		percision;
	char	conv_char;
	int		type;
	char	large;
}		t_prntf_arg;

int		cmd_type(char c);
void	fix_str(char *str);
char	*ft_itoa_sb(long long num, int base);
char	*ft_itoa_ub(unsigned long long num, int base);
char	*process_number_arg(t_prntf_arg cmd, va_list *vlst);
char	*process_char_arg(t_prntf_arg cmd, va_list *vlst);
void	parse_comand(char *command, t_prntf_arg* arg);
char	*append(char *str, char *to_append);
char	*apply_min_width(char *str, char filler, int bound, int minw);

#endif