/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 04:57:53 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/05/18 18:22:23 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	unsigned int	i;
	__uint128_t		*ptr_dst;
	__uint128_t		*ptr_src;

	i = 0;
	while (i < n % 16)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	ptr_dst = (__uint128_t *)(dst + i);
	ptr_src = (__uint128_t *)(src + i);
	while (ptr_dst != dst + n)
		*ptr_dst++ = *ptr_src++;
	return (dst);
}
