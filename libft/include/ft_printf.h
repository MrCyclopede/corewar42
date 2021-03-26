/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 06:03:08 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/19 05:38:33 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define FALSE 0
# define TRUE 1
# define BUFF_SIZE 64
# define CHAR 0
# define STR 1
# define PTR 2
# define INT 3
# define ALSO_INT 4
# define OCTAL 5
# define UNS_INT 6
# define HEX 7
# define MAJ_HEX 8
# define FLOAT 9
# define PERCENT 10
# define CAP_FLOAT 11
# define BINARY 12
# define COLORS 13
# define TABLE 14
# define INV_CONV 15

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

typedef struct		s_buff
{
	char			buff[BUFF_SIZE];
	int				index;
	int				flushed;
}					t_buff;

typedef struct		s_conv
{
	va_list			*args;
	char			*format;
	char			str[64];
	char			*s;
	int				len;
	int				acc_changed;
	int				neg;
	int				minus;
	int				plus;
	int				zero;
	int				space;
	int				hashtag;
	int				width;
	int				acc;
	int				size;
	int				conv;
	int				from_tab;
	int				depth;
	t_buff			*buff;
}					t_conv;

typedef int			(*t_farray)(t_conv *conv, t_buff *buff);

int					ft_printf(char *format, ...);
int					c(t_conv *conv, t_buff *buff);
int					s(t_conv *conv, t_buff *buff);
int					p(t_conv *conv, t_buff *buff);
int					d(t_conv *conv, t_buff *buff);
int					o(t_conv *conv, t_buff *buff);
int					u(t_conv *conv, t_buff *buff);
int					x(t_conv *conv, t_buff *buff);
int					f(t_conv *conv, t_buff *buff);
int					b(t_conv *conv, t_buff *buff);
int					t(t_conv *conv, int i, void *tab, int depth);
void				cast_tab_f(t_buff *buff, t_conv *conv, void *tab, int size);
void				cast_tab_oux(t_buff *buff, t_conv *conv,
														void *tab, int size);
void				cast_tab_di(t_buff *buff, t_conv *conv,
														void *tab, int size);
void				cast_tab_str(t_buff *buff, t_conv *conv,
														void *tab, int size);
void				cast_tab_char(t_buff *buff, t_conv *conv, void *tab);
void				conversion_manager(t_conv *conv, t_buff *buff, int y);
int					colors(t_conv *conv, t_buff *buff);
int					invalid_conv(t_conv *conv, t_buff *buff);
int					acc(t_conv *conv, char *str);
int					width(t_conv *conv, char *str);
int					flags(t_conv *conv, char c);
int					size_hhll(t_conv *conv, char *str);
void				buff_flush(t_buff *buff);
void				buff_insert_str(t_buff *buff, t_conv *conv);
void				buff_insert_actual_str(t_buff *buff, char *str);
void				buff_insert_actual_str_conditional(t_buff *buff,
														char *str, int check);
void				buff_insert_char(t_buff *buff, char c);
int					print_itoa_base(char *s,
					unsigned long long int n, int base, int opt);
int					print_ftoa(t_conv *conv, long double f);
int					dispatch_cast(t_conv *conv);
void				fill_f_array(t_farray *farray);
int					fill_conv(t_conv *conv, int i, char *conversions,
																t_buff *buff);
#endif
