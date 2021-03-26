/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:14:30 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/19 05:38:52 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	default_conv(t_conv *conv)
{
	conv->acc = 1;
}

int			find_conv(t_conv *conv, char c, char *conversions)
{
	int x;

	x = 0;
	while (conversions[x])
	{
		if (conversions[x] == c)
		{
			conv->conv = x;
			if ((conv->conv == FLOAT
						|| conv->conv == CAP_FLOAT) && !conv->acc_changed)
				conv->acc = 6;
			return (1);
		}
		x++;
	}
	return (0);
}

int			fill_conv(t_conv *conv, int i, char *conversions, t_buff *buff)
{
	int initial;

	conv->buff = buff;
	default_conv(conv);
	while (flags(conv, conv->format[i]))
		i++;
	i += width(conv, &conv->format[i]);
	if (conv->format[i] == '.')
	{
		conv->acc_changed = TRUE;
		i += acc(conv, &conv->format[i]);
	}
	if (size_hhll(conv, &conv->format[i]))
		i += size_hhll(conv, &conv->format[i]);
	initial = i;
	if (find_conv(conv, conv->format[i], conversions))
		return (i + 1);
	conv->conv = INV_CONV;
	return (initial);
}
