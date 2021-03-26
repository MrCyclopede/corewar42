/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:13:59 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/19 05:37:08 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			conv_handler(t_conv *conv, int i, t_buff *buff, t_farray *farray)
{
	i = fill_conv(conv, i + 1, "cspdiouxXf%Fb~t", buff);
	if (conv->conv == TABLE)
		i = t(conv, i, NULL, 0);
	else
		farray[conv->conv](conv, buff);
	return (i);
}

int			ft_printf(char *format, ...)
{
	int			i;
	va_list		arg_list;
	t_buff		buff;
	t_farray	farray[INV_CONV + 1];
	t_conv		conv;

	i = 0;
	va_start(arg_list, format);
	ft_bzero(&buff, sizeof(t_buff));
	fill_f_array(farray);
	while (format[i])
	{
		if (format[i] == '%')
		{
			ft_bzero(&conv, sizeof(t_conv));
			conv.format = format;
			conv.args = &arg_list;
			i = conv_handler(&conv, i, &buff, farray);
		}
		else
			buff_insert_char(&buff, format[i++]);
	}
	buff_flush(&buff);
	return (buff.flushed);
}
