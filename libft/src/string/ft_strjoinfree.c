/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 00:18:03 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/05/18 18:28:33 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char **s1, char **s2, int o)
{
	char	*ret;

	if (!*s1 && !*s2)
		return (NULL);
	if (!*s1)
		ret = ft_strdup(*s2);
	if (!*s2)
		ret = ft_strdup(*s1);
	if (*s1 && *s2)
		ret = ft_strjoin(*s1, *s2);
	if ((*s1) && (o == 1 || o == 3))
		ft_strdel(s1);
	if ((*s2) && (o == 2 || o == 3))
		ft_strdel(s2);
	return (ret);
}
