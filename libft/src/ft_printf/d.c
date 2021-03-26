/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 06:16:39 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/19 03:40:16 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	padding(t_conv *conv, t_buff *buff)
{
	int i;

	i = conv->width - (conv->len + conv->acc);
	while (i-- > 0)
	{
		if (conv->zero)
			buff_insert_char(buff, '0');
		else
			buff_insert_char(buff, ' ');
	}
	return (0);
}

static int	sign(t_conv *conv, t_buff *buff)
{
	if (conv->plus && !conv->neg)
		buff_insert_char(buff, '+');
	else if (conv->neg)
		buff_insert_char(buff, '-');
	else if (conv->space && !conv->neg)
		buff_insert_char(buff, ' ');
	else
		return (-1);
	return (0);
}

static int	precision(t_conv *conv, t_buff *buff)
{
	int i;

	i = conv->acc;
	while (i-- > 0)
		buff_insert_char(buff, '0');
	return (0);
}

static void	adapt_conv(t_conv *conv)
{
	if (conv->acc == 0 && (ft_atoi(conv->str) == 0))
	{
		conv->len = 0;
		conv->str[0] = '\0';
	}
	if (conv->zero && conv->minus)
		conv->zero = 0;
	if (conv->zero && (conv->conv >= INT &&
							conv->conv <= MAJ_HEX) && conv->acc != 1)
		conv->zero = 0;
	conv->len = ft_strlen(conv->str) + (conv->neg || conv->space || conv->plus);
	conv->acc = conv->acc - ft_strlen(conv->str);
	if (conv->acc < 0)
		conv->acc = 0;
}

int			d(t_conv *conv, t_buff *buff)
{
	int j;

	j = buff->flushed + buff->index;
	if (!conv->from_tab)
		dispatch_cast(conv);
	adapt_conv(conv);
	if (conv->zero)
		sign(conv, buff);
	if (!conv->minus && !(conv->zero
				&& (conv->minus || conv->space || conv->plus)))
		padding(conv, buff);
	if (!conv->zero)
		sign(conv, buff);
	if (conv->zero && (conv->minus || conv->space || conv->plus))
		padding(conv, buff);
	precision(conv, buff);
	buff_insert_str(buff, conv);
	if (conv->minus)
		padding(conv, buff);
	return ((buff->flushed + buff->index) - j);
}
