/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 05:19:17 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/19 03:42:30 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	padding(t_conv *conv, t_buff *buff)
{
	int i;

	if (conv->acc > conv->len)
		i = conv->width - (conv->acc + conv->hashtag);
	else
		i = conv->width - (conv->len + conv->hashtag);
	while (i-- > 0)
	{
		if (conv->zero)
			buff_insert_char(buff, '0');
		else
			buff_insert_char(buff, ' ');
	}
	return (0);
}

static int	hashtag(t_conv *conv, t_buff *buff)
{
	if (conv->hashtag && ft_atoi(conv->str))
		buff_insert_char(buff, '0');
	else if (conv->hashtag && !conv->acc)
		buff_insert_char(buff, '0');
	return (0);
}

static int	precision(t_conv *conv, t_buff *buff)
{
	int i;

	i = conv->acc - conv->len;
	while (i-- > 0)
		buff_insert_char(buff, '0');
	return (0);
}

static void	adapt_conv(t_conv *conv)
{
	if (conv->minus)
		conv->zero = 0;
	if (conv->acc == 0 && !ft_atoi(conv->str))
	{
		conv->len = 0;
		conv->str[0] = '\0';
	}
	if (conv->zero && conv->acc_changed)
		conv->zero = 0;
	conv->len = ft_strlen(conv->str);
	if (conv->hashtag && conv->str[0] != '0' && conv->len >= conv->acc)
		conv->acc++;
	else if (conv->str[0] == '0' || conv->acc > conv->len)
		conv->hashtag = 0;
}

int			o(t_conv *conv, t_buff *buff)
{
	int j;

	j = buff->flushed + buff->index;
	if (!conv->from_tab)
		dispatch_cast(conv);
	adapt_conv(conv);
	if (conv->zero && conv->hashtag)
		hashtag(conv, buff);
	if (!conv->minus
			&& !(conv->zero && (conv->minus || conv->space || conv->plus)))
		padding(conv, buff);
	if (!conv->zero)
		hashtag(conv, buff);
	if (conv->zero && (conv->minus || conv->space || conv->plus))
		padding(conv, buff);
	precision(conv, buff);
	buff_insert_str(buff, conv);
	if (conv->minus)
		padding(conv, buff);
	return ((buff->flushed + buff->index) - j);
}
