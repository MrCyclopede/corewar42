/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:51:21 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/20 13:29:23 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long len;

	len = n;
	if (ft_strlen(s1) + 1 < n)
		len = ft_strlen(s1) + 1;
	if (ft_strlen(s2) + 1 < len)
		len = ft_strlen(s1) + 1;
	return (ft_memcmp(s1, s2, len));
}
