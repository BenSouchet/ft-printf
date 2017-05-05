/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:38:57 by bsouchet          #+#    #+#             */
/*   Updated: 2017/05/05 19:19:44 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			color(t_printf *p)
{
	int len;

	p->printed = 5;
	if (!ft_strncmp(p->format, "{red}", (len = 5)))
		buffer(p, PF_RED, p->printed);
	else if (!ft_strncmp(p->format, "{green}", (len = 7)))
		buffer(p, PF_GREEN, p->printed);
	else if (!ft_strncmp(p->format, "{yellow}", (len = 8)))
		buffer(p, PF_YELLOW, p->printed);
	else if (!ft_strncmp(p->format, "{blue}", (len = 6)))
		buffer(p, PF_BLUE, p->printed);
	else if (!ft_strncmp(p->format, "{purple}", (len = 8)))
		buffer(p, PF_PURPLE, p->printed);
	else if (!ft_strncmp(p->format, "{cyan}", (len = 6)))
		buffer(p, PF_CYAN, p->printed);
	else if (!ft_strncmp(p->format, "{eoc}", (len = 5)))
		buffer(p, PF_EOC, --p->printed);
	else if (!(len = 0))
		p->printed = 0;
	p->format += len - 1;
	p->len += p->printed;
	//--p->format;
}

static void		ldtoa_fill(double n, t_printf *p, long value)
{
	int		len;
	int		accuracy;
	char	s[48];

	len = p->printed - 1 - p->precision;
	accuracy = p->printed - 1 - len;
	while (accuracy--)
	{
		s[len + accuracy + 1] = value % 10 + '0';
		value /= 10;
	}
	(p->precision > 0) ? s[len] = '.' : 0;
	value = (long)(ABS(n));
	while (++accuracy < len)
	{
		s[len - accuracy - 1] = value % 10 + '0';
		value /= 10;
	}
	(p->f & F_APP_PRECI && p->f & F_ZERO) ? s[0] = ' ' : 0;
	(p->f & F_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & F_PLUS && n >= 0) ? s[0] = '+' : 0;
	buffer(p, s, len + 1 + 6);
}

void			pf_putdouble(t_printf *p)
{
	double		n;
	long		tmp;
	int			len;
	double		decimal;
	long		value;

	n = (double)va_arg(p->ap, double);
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	if (!(p->f & F_APP_PRECI))
		p->precision = 6;
	len = (p->precision > 0) ? 1 : 0;
	tmp = (long)(ABS(n));
	while (tmp && ++len)
		tmp /= 10;
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	p->printed = p->precision + len + ((n < 0) ? 1 : 0);
	decimal = ((n < 0.0f) ? -n : n);
	decimal = (decimal - (long)(((n < 0.0f) ? -n : n))) *
	ft_pow(10, p->precision + 1);
	decimal = ((long)decimal % 10 > 4) ? (decimal) / 10 + 1 : decimal / 10;
	value = (int)decimal;
	ldtoa_fill(n, p, value);
}
