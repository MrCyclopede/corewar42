/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 03:33:31 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/19 07:29:30 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		buffer_manager(t_conv *conv, t_conv *deeper_conv, int depth, int action)
{
	int	w;

	w = 0;
	if (action == 1)
	{
		while (w++ < depth)
			buff_insert_char(conv->buff, '\t');
		buff_insert_char(conv->buff, '[');
		if (deeper_conv->conv == TABLE)
			buff_insert_char(conv->buff, '\n');
		else if (deeper_conv->conv != TABLE)
			return (1);
	}
	else if (action == 2)
		while (w++ < depth)
			buff_insert_char(conv->buff, '\t');
	return (0);
}

int		disp_d_conv(t_conv *conv, t_conv *deeper_conv, void *tab)
{
	deeper_conv->from_tab = 1;
	if (deeper_conv->conv == INT || deeper_conv->conv == ALSO_INT)
		cast_tab_di(conv->buff, deeper_conv, tab, conv->width);
	else if (deeper_conv->conv == OCTAL || deeper_conv->conv == UNS_INT
			|| deeper_conv->conv == HEX || deeper_conv->conv == MAJ_HEX
			|| deeper_conv->conv == BINARY || deeper_conv->conv == PTR)
		cast_tab_oux(conv->buff, deeper_conv, tab, conv->width);
	else if (deeper_conv->conv == FLOAT || deeper_conv->conv == CAP_FLOAT)
		cast_tab_f(conv->buff, deeper_conv, tab, conv->width);
	else if (deeper_conv->conv == CHAR)
		cast_tab_char(conv->buff, deeper_conv, tab);
	else if (deeper_conv->conv == STR)
		cast_tab_str(conv->buff, deeper_conv, tab, conv->width);
	else
		return (1);
	return (0);
}

int		t_init(t_conv *conv, t_conv *deeper_conv, int i)
{
	ft_bzero(deeper_conv, sizeof(t_conv));
	deeper_conv->args = conv->args;
	deeper_conv->format = conv->format;
	if (conv->format[i] == '%')
		i = fill_conv(deeper_conv, i + 1, "cspdiouxXf%Fb~t", conv->buff);
	return (i);
}

int		t_recursion(t_conv *deeper_conv, t_conv *conv, void *tab, int *ints)
{
	int i;
	int	j;

	j = 0;
	while (j < conv->width)
	{
		i = t(deeper_conv, ints[0], *(void **)tab, ints[1] + 1);
		if (j++ != conv->width - 1)
			buff_insert_char(conv->buff, ',');
		buff_insert_char(conv->buff, '\n');
		tab = (char *)tab + sizeof(void *);
	}
	return (i);
}

int		t(t_conv *conv, int i, void *tab, int depth)
{
	int		normifixer[2];
	int		marker;
	t_conv	deeper_conv;

	marker = 0;
	i = t_init(conv, &deeper_conv, i);
	normifixer[1] = depth;
	normifixer[0] = i;
	if (!tab)
		tab = va_arg(*(conv->args), void *);
	if (buffer_manager(conv, &deeper_conv, normifixer[1], 1))
		marker = 1;
	if (deeper_conv.conv != TABLE)
		while (disp_d_conv(conv, &deeper_conv, tab))
			return (i);
	else
		i = t_recursion(&deeper_conv, conv, tab, normifixer);
	if (!marker)
		buffer_manager(conv, &deeper_conv, normifixer[1], 2);
	buff_insert_char(conv->buff, ']');
	return (i);
}
