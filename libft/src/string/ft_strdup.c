/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 09:00:43 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/19 19:13:09 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *new;

	if (!(new = ft_memalloc(ft_strlen(s1) + 1)))
		return (NULL);
	ft_strcpy(new, s1);
	new[ft_strlen(s1)] = '\0';
	return (new);
}
