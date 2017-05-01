/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 00:02:06 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/01 20:14:41 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		buffer(t_printf *p, void *new, size_t size)
{
	int			diff;
	long long	new_i;

	new_i = 0;
	while (PF_BUF_SIZE - p->buffer_index < (int)size)
	{
		diff = PF_BUF_SIZE - p->buffer_index;
		ft_memcpy(&(p->buff[p->buffer_index]), &(new[new_i]), diff);
		size -= diff;
		new_i += diff;
		p->buffer_index += diff;
		p->len += diff;
		write(p->fd, p->buff, p->buffer_index);
		p->buffer_index = 0;
	}
	ft_memcpy(&(p->buff[p->buffer_index]), &(new[new_i]), size);
	p->buffer_index += size;
//	p->len += size;
}

void		buffer_flush(t_printf *p)
{
    write(p->fd, p->buff, p->buffer_index);
}
