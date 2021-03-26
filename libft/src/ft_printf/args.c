/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:06:07 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/17 07:39:10 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "stdio.h"

static long long			cast_size_di(t_conv *conv)
{
	if (conv->size == 0)
		return (va_arg(*(conv->args), int));
	else if (conv->size == 1)
		return ((short int)va_arg(*(conv->args), int));
	else if (conv->size == 2)
		return ((signed char)va_arg(*(conv->args), int));
	else if (conv->size == 3)
		return ((signed long)va_arg(*(conv->args), long));
	else if (conv->size == 4)
		return (va_arg(*(conv->args), long long));
	else if (conv->size == 6)
		return (va_arg(*(conv->args), long long));
	else if (conv->size == 7)
		return (va_arg(*(conv->args), long long));
	return (0);
}

static unsigned long long	cast_size_oux(t_conv *conv)
{
	if (conv->size == 0)
		return (va_arg(*(conv->args), unsigned int));
	else if (conv->size == 1)
		return ((short unsigned int)va_arg(*(conv->args), unsigned int));
	else if (conv->size == 2)
		return ((unsigned char)va_arg(*(conv->args), unsigned int));
	else if (conv->size == 3)
		return (va_arg(*(conv->args), unsigned long int));
	else if (conv->size == 4)
		return (va_arg(*(conv->args), unsigned long long int));
	else if (conv->size == 6)
		return (va_arg(*(conv->args), unsigned long long int));
	else if (conv->size == 7)
		return (va_arg(*(conv->args), unsigned long long int));
	return (0);
}

static int					cast_size_f(t_conv *conv)
{
	long double f;

	f = 0.0;
	if (conv->conv == FLOAT || conv->conv == CAP_FLOAT)
	{
		if (conv->size == 0)
			f = va_arg(*(conv->args), double);
		else if (conv->size == 3)
			f = va_arg(*(conv->args), double);
		else if (conv->size == 5)
			f = va_arg(*(conv->args), long double);
		else
			return (0);
		if (f < 0)
		{
			f = f * -1;
			conv->neg = TRUE;
		}
		if (print_ftoa(conv, f))
			return (1);
	}
	return (0);
}

static void					cast_csp_percent(t_conv *conv)
{
	unsigned long int	y;

	if (conv->conv == CHAR)
	{
		conv->str[0] = (char)va_arg(*(conv->args), int);
		conv->str[1] = '\0';
	}
	else if (conv->conv == PERCENT)
	{
		conv->str[0] = '%';
		conv->str[1] = '\0';
	}
	else if (conv->conv == STR)
	{
		if (!(conv->s = va_arg(*(conv->args), char *)))
			conv->s = "(null)";
	}
	else if (conv->conv == PTR)
	{
		y = va_arg(*(conv->args), unsigned long int);
		print_itoa_base(conv->str, y, 16, 1);
	}
}

int							dispatch_cast(t_conv *conv)
{
	long long int	x;

	cast_csp_percent(conv);
	if (cast_size_f(conv))
		return (1);
	if (conv->conv == INT || conv->conv == ALSO_INT)
	{
		x = cast_size_di(conv);
		if (x < 0 && (conv->neg = TRUE))
			x = x * -1;
		print_itoa_base(conv->str, x, 10, 1);
	}
	else if (conv->conv == OCTAL)
		print_itoa_base(conv->str, cast_size_oux(conv), 8, 1);
	else if (conv->conv == UNS_INT)
		print_itoa_base(conv->str, cast_size_oux(conv), 10, 1);
	else if (conv->conv == HEX)
		print_itoa_base(conv->str, cast_size_oux(conv), 16, 1);
	else if (conv->conv == MAJ_HEX)
		print_itoa_base(conv->str, cast_size_oux(conv), 16, 2);
	else if (conv->conv == BINARY)
		print_itoa_base(conv->str, cast_size_oux(conv), 2, 1);
	return (0);
}
