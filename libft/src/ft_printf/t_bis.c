/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_bis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 03:33:31 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/21 02:33:24 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		cast_tab_f(t_buff *buff, t_conv *conv, void *tab, int size)
{
	int				i;
	long double		float_double;
	t_conv			conv_cpy;

	ft_memcpy(&conv_cpy, conv, sizeof(t_conv));
	i = -1;
	while (++i < size)
	{
		ft_memcpy(conv, &conv_cpy, sizeof(t_conv));
		if (i != 0)
			buff_insert_actual_str(buff, ", ");
		if (conv->size == 0)
			float_double = (long double)((float *)tab)[i];
		else if (conv->size == 3)
			float_double = (long double)((double *)tab)[i];
		else if (conv->size == 5)
			float_double = (long double)((long double *)tab)[i];
		if (float_double < 0 && (conv->neg = TRUE))
			float_double = float_double * -1;
		print_ftoa(conv, float_double);
		f(conv, buff);
	}
}

void		cast_tab_oux(t_buff *buff, t_conv *conv, void *tab, int size)
{
	int						i;
	unsigned long long int	y;
	t_conv					conv_cpy;

	ft_memcpy(&conv_cpy, conv, sizeof(t_conv));
	i = -1;
	while (++i < size)
	{
		ft_memcpy(conv, &conv_cpy, sizeof(t_conv));
		buff_insert_actual_str_conditional(buff, ", ", i);
		if (conv->size == 2)
			y = (long long)((unsigned char *)tab)[i];
		else if (conv->size == 1)
			y = (long long)((short unsigned int *)tab)[i];
		else if (conv->size == 0)
			y = (long long)((unsigned int *)tab)[i];
		else if (conv->size == 3 || conv->size == 7)
			y = (long long)((unsigned long int *)tab)[i];
		else if (conv->size == 4 || conv->size == 6)
			y = (long long)((unsigned long long int *)tab)[i];
		conversion_manager(conv, buff, y);
	}
}

void		cast_tab_di(t_buff *buff, t_conv *conv, void *tab, int size)
{
	int				i;
	long long int	x;
	t_conv			conv_cpy;

	ft_memcpy(&conv_cpy, conv, sizeof(t_conv));
	i = -1;
	while (++i < size)
	{
		ft_memcpy(conv, &conv_cpy, sizeof(t_conv));
		buff_insert_actual_str_conditional(buff, ", ", i);
		if (conv->size == 2)
			x = (long long)((signed char *)tab)[i];
		else if (conv->size == 1)
			x = (long long)((short int *)tab)[i];
		else if (conv->size == 0)
			x = (long long)((int *)tab)[i];
		else if (conv->size == 3 || conv->size == 7)
			x = (long long)((long int *)tab)[i];
		else if (conv->size == 4 || conv->size == 6)
			x = (long long)((long long int *)tab)[i];
		if (x < 0 && (conv->neg = TRUE))
			x = x * -1;
		print_itoa_base(conv->str, x, 10, 1);
		d(conv, buff);
	}
}

void		cast_tab_str(t_buff *buff, t_conv *conv, void *tab, int size)
{
	int				i;
	t_conv			conv_cpy;

	ft_memcpy(&conv_cpy, conv, sizeof(t_conv));
	i = 0;
	while (i < size)
	{
		ft_memcpy(conv, &conv_cpy, sizeof(t_conv));
		if (i != 0)
		{
			buff_insert_char(buff, ',');
			buff_insert_char(buff, ' ');
		}
		conv->s = ((char **)tab)[i];
		i++;
		s(conv, buff);
	}
}

void		cast_tab_char(t_buff *buff, t_conv *conv, void *tab)
{
	if (tab)
		conv->s = (char *)tab;
	else
		conv->s = "(null)";
	s(conv, buff);
}
