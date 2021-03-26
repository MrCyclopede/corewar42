/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:14:30 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/17 05:55:42 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			flags(t_conv *conv, char c)
{
	if (c == '-')
		conv->minus = TRUE;
	else if (c == '+')
		conv->plus = TRUE;
	else if (c == '0')
		conv->zero = TRUE;
	else if (c == ' ')
		conv->space = TRUE;
	else if (c == '#')
		conv->hashtag = TRUE;
	else
		return (0);
	return (1);
}

int			width(t_conv *conv, char *str)
{
	int i;

	i = 0;
	if (str[i] == '*')
	{
		conv->width = va_arg(*(conv->args), int);
		return (1);
	}
	if (ft_isdigit(str[i]))
	{
		conv->width = ft_atoi(str);
		while (ft_isdigit(str[i]))
			i++;
	}
	if (conv->width < 0)
		conv->width *= -1;
	return (i);
}

int			acc(t_conv *conv, char *str)
{
	int i;

	i = 0;
	if (str[i + 1] == '*')
	{
		conv->acc = va_arg(*(conv->args), int);
		return (2);
	}
	conv->acc = ft_atoi(&str[i + 1]);
	while (ft_isdigit(str[i + 1]))
		i++;
	i++;
	return (i);
}

static int	size_ljz(t_conv *conv, char *str)
{
	if (str[0] == 'L')
	{
		conv->size = 5;
		return (1);
	}
	if (str[0] == 'j')
	{
		conv->size = 6;
		return (1);
	}
	if (str[0] == 'z')
	{
		conv->size = 7;
		return (1);
	}
	return (0);
}

int			size_hhll(t_conv *conv, char *str)
{
	if (str[0] == 'h')
	{
		if (str[1] == 'h')
			return (conv->size = 2);
		else
			return (conv->size = 1);
	}
	if (str[0] == 'l')
	{
		if (str[1] == 'l')
		{
			conv->size = 4;
			return (2);
		}
		else
		{
			conv->size = 3;
			return (1);
		}
	}
	return (size_ljz(conv, str));
}
