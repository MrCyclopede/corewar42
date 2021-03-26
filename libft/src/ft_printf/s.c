/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 15:23:52 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/19 03:44:05 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	padding(t_conv *conv, t_buff *buff)
{
	int i;

	i = conv->width - conv->len;
	while (i-- > 0)
	{
		buff_insert_char(buff, ' ');
	}
	return (0);
}

static void	format_conv(t_conv *conv)
{
	if (conv->acc == 0)
		return ;
	conv->len = ft_strlen(conv->s);
	if (conv->acc != 1 && conv->acc < conv->len)
	{
		conv->len = conv->acc;
	}
}

int			s(t_conv *conv, t_buff *buff)
{
	int i;

	i = 0;
	if (!conv->from_tab)
		dispatch_cast(conv);
	format_conv(conv);
	if (!conv->minus)
		padding(conv, buff);
	while (i < conv->len && conv->acc != 0)
	{
		buff_insert_char(buff, conv->s[i]);
		i++;
	}
	if (conv->minus)
		padding(conv, buff);
	return (0);
}
