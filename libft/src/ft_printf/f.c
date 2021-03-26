/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:38:11 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/19 03:42:08 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	padding(t_conv *conv, t_buff *buff)
{
	int i;

	i = conv->width - (conv->len + conv->acc
			+ (conv->space || conv->plus || conv->neg));
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

static int	adapt_conv(t_conv *conv)
{
	conv->len = ft_strlen(conv->str);
	return (1);
}

int			f(t_conv *conv, t_buff *buff)
{
	int j;

	j = buff->flushed + buff->index;
	if (!conv->from_tab)
		dispatch_cast(conv);
	adapt_conv(conv);
	if (conv->zero)
		sign(conv, buff);
	if (!conv->minus
			&& !(conv->zero && (conv->minus || conv->space || conv->plus)))
		padding(conv, buff);
	if (!conv->zero)
		sign(conv, buff);
	if (conv->zero && (conv->minus || conv->space || conv->plus))
		padding(conv, buff);
	buff_insert_str(buff, conv);
	precision(conv, buff);
	if (conv->minus)
		padding(conv, buff);
	return ((buff->flushed + buff->index) - j);
}
