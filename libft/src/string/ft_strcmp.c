/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:31:42 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/16 23:57:23 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t x;

	if (ft_strlen(s1) > ft_strlen(s2))
		x = ft_strlen(s1);
	else
		x = ft_strlen(s2);
	return (ft_memcmp(s1, s2, x));
}
