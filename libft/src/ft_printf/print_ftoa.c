/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ftoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 00:34:11 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/16 23:54:48 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long int	round_cast(double f)
{
	double	fcpy;
	int		i;

	i = 0;
	fcpy = f - (int)f;
	fcpy *= 10;
	if ((int)fcpy % 10 == 5)
	{
		fcpy *= 10;
		i++;
		while ((int)fcpy % 10 == 0 && i < 20)
		{
			fcpy -= (unsigned long long)fcpy;
			fcpy *= 10;
			i++;
		}
		if ((int)fcpy % 10 > 0)
		{
			f++;
			return ((unsigned long long int)f);
		}
	}
	else if ((unsigned long long)fcpy % 10 > 5)
		f++;
	return ((unsigned long long int)f);
}

static unsigned long long int	get_float_part(t_conv *conv, double f)
{
	int i;

	i = 0;
	while (i < conv->acc)
	{
		f *= 10;
		i++;
	}
	return (round_cast(f));
}

static int						special_values(t_conv *conv, long double f,
		long double long_positive_inf, long double long_negative_inf)
{
	if (f == 0)
	{
		if (1 / f < 0)
			conv->neg = TRUE;
		return (0);
	}
	else if (f == long_positive_inf)
	{
		conv->acc = 0;
		ft_strcpy(conv->str, "inf");
		return (1);
	}
	else if (f == long_negative_inf)
	{
		conv->acc = 0;
		ft_strcpy(conv->str, "-inf");
		return (1);
	}
	else if (f != f)
	{
		conv->acc = 0;
		ft_strcpy(conv->str, "nan");
		return (1);
	}
	return (0);
}

static void						combine_fstr(t_conv *conv, char *i, char *f)
{
	ft_strcpy(conv->str, i);
	if (conv->hashtag)
		conv->str[conv->len] = '.';
	if (conv->acc)
	{
		conv->acc -= ft_strlen(f);
		conv->str[conv->len] = '.';
		ft_strcpy(&conv->str[conv->len + 1], f);
	}
}

int								print_ftoa(t_conv *conv, long double f)
{
	unsigned long long int	temp;
	char					integer[32];
	char					floating[31];

	if (special_values(conv, f, 1.0 / 0.0, -1.0 / 0.0) == 1)
		return (1);
	if (!conv->acc)
		temp = round_cast(f);
	else
		temp = (unsigned long long)f;
	if (!temp)
		conv->str[0] = '0';
	print_itoa_base(integer, temp, 10, 1);
	conv->len = ft_strlen(integer);
	f -= (unsigned long long int)f;
	temp = get_float_part(conv, f);
	print_itoa_base(floating, temp, 10, 1);
	combine_fstr(conv, integer, floating);
	conv->len = ft_strlen(conv->str);
	return (0);
}
