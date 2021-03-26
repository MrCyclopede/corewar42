/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 00:35:41 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/11 01:52:45 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t x;

	x = 0;
	while (x < n)
	{
		((unsigned char *)dst)[x] = ((const unsigned char *)src)[x];
		if (((unsigned char *)dst)[x] == (unsigned char)c)
			return (dst + x + 1);
		x++;
	}
	return (NULL);
}
