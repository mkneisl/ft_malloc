/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:29:49 by mkneisl           #+#    #+#             */
/*   Updated: 2025/02/25 15:29:55 by mkneisl          ###   ########.fr       */
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
}		t_prntf_arg;

int					is_cmd(char c);
void				fix_str(char *str);
char				*ft_itoa_sb(long long num, int base);
char				*ft_itoa_ub(unsigned long long num, int base);
char				*process_number_arg(t_prntf_arg cmd, va_list *vlst);
char				*process_char_arg(t_prntf_arg cmd, va_list *vlst);
t_prntf_arg			parse_comand(char *command);
char				*append(char *str, char *to_append);

#endif