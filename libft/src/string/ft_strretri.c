/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strretri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:18:31 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/05/18 18:28:59 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strretri(char *s, char c, int len)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (!s)
		return (NULL);
	while (s[i] != c && i < len)
		i++;
	if (len <= i)
		return (NULL);
	if (!(ret = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_strncpy(ret, s, i);
	ret[i] = '\0';
	return (ret);
}
