/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:50:01 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/05/18 18:21:59 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	__uint128_t		*ptr;

	i = 0;
	while (i < n % 16)
	{
		((unsigned char *)s)[i] = (unsigned char)0;
		i++;
	}
	ptr = (__uint128_t *)(s + i);
	while (ptr != s + n)
		*ptr++ = (__uint128_t)0;
}
