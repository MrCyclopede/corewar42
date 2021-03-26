/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:35:30 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/13 02:50:48 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	buff_flush(t_buff *buff)
{
	buff->flushed += write(1, buff->buff, buff->index);
	ft_bzero((void *)buff->buff, BUFF_SIZE);
	buff->index = 0;
}

void	buff_insert_str(t_buff *buff, t_conv *conv)
{
	int i;

	i = 0;
	while (conv->str[i] && i < conv->len)
	{
		buff_insert_char(buff, conv->str[i]);
		i++;
	}
}

void	buff_insert_actual_str(t_buff *buff, char *str)
{
	int i;

	i = 0;
	while (str[i])
		buff_insert_char(buff, str[i++]);
}

void	buff_insert_actual_str_conditional(t_buff *buff, char *str, int check)
{
	int i;

	i = 0;
	if (!check)
		return ;
	while (str[i])
		buff_insert_char(buff, str[i++]);
}

void	buff_insert_char(t_buff *buff, char c)
{
	if (buff->index >= BUFF_SIZE)
		buff_flush(buff);
	buff->buff[buff->index] = c;
	buff->index++;
}
