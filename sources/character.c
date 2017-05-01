/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/01 20:14:46 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** handles %%
*/

int		percent_char(t_printf *p)
{
	if (!(p->f & F_MINUS) && p->min_length - 1 > 0)
		ft_putnchar(p->min_length - 1, (p->f & F_ZERO) ? '0' : ' ');
	ft_putwchar('%', 4);
	if (p->f & F_MINUS)
		ft_putnchar(p->min_length - 1, (p->f & F_ZERO) ? '0' : ' ');
	return (MAX(p->min_length, 1));
}

/*
** returns a single character len and display it
** refer to libft for putwchar amd wcharlen functions
*/

void	pf_character(t_printf *p)
{
	unsigned	c;
	int			len;

	c = va_arg(p->ap, unsigned);
	len = (p->f & LM_LONG || p->f & LM_LONG2) ? ft_wcharlen(c) : 1;
	if (!(p->f & F_MINUS))
		ft_putnchar(p->min_length - MIN(len, p->min_length),
		(p->f & F_ZERO) ? '0' : ' ');
	(p->f & LM_LONG || p->f & LM_LONG2) ? ft_putwchar(c, 4) : ft_putchar(c);
	if (p->f & F_MINUS)
		ft_putnchar(p->min_length - MIN(len, p->min_length), ' ');
	p->len += MAX(p->min_length, len);
}
