/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 08:51:55 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/17 03:50:12 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t l1;
	size_t l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (l2 < n)
		ft_strcpy(&s1[l1], s2);
	else
	{
		ft_strncpy(&s1[l1], s2, n);
		s1[l1 + n] = '\0';
	}
	return (s1);
}
