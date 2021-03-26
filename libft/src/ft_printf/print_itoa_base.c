/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_itoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 00:25:06 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/16 02:45:17 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reverse(char *str)
{
	int		i;
	int		j;
	int		x;
	char	c;

	j = 0;
	i = 0;
	while (str[i])
		i++;
	i--;
	x = i / 2;
	while (j <= x)
	{
		c = str[i];
		str[i] = str[j];
		str[j] = c;
		j++;
		i--;
	}
}

void	capitalise(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 'a' - 'A';
		i++;
	}
}

int		print_itoa_base(char *s, unsigned long long int n, int base, int opt)
{
	char	str[128];
	char	*base_str;
	int		i;

	i = 0;
	base_str = "0123456789abcdef";
	if (n == 0)
	{
		ft_strcpy(s, "0");
		return (0);
	}
	while (n > 0)
	{
		str[i] = base_str[n % base];
		n = n / base;
		i++;
	}
	str[i] = '\0';
	reverse(str);
	if (opt == 2)
		capitalise(str);
	ft_strcpy(s, str);
	return (0);
}
