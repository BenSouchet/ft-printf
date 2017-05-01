/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:16:05 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/01 20:15:01 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


void	parse_optionals(t_printf *p)
{
	p->f = 0;
	p->printed = 0;
	p->min_length = 0;
	p->precision = 1;
	parse_flags(&p->f, p);
	field_width(p, &p->min_length);
	precision(p, 0);
	length_modifier(p, &p->f);
	parse_flags(&p->f, p);
	conversion_specifier(p);
}

void	parse_flags(short *flags, t_printf *p)
{
	int		tmp;
	short	n;

	while ((n = ft_strchr_index("#0+- *", *p->format)) > -1 && ++p->format)
		*flags |= (1 << n);
	if (*flags & F_MINUS)
		*flags &= ~F_ZERO;
	if (*flags & F_PLUS)
		*flags &= ~F_SPACE;
	if (*flags & F_WILDCARD)
	{
		tmp = (int)va_arg(p->ap, int);
		*flags = (tmp < 0) ? *flags | F_MINUS : *flags & ~F_MINUS;
		tmp = ABS(tmp);
		if (!(*flags & F_APP_PRECI))
			p->min_length = tmp;
		else
		{
			p->precision = (!(*flags & F_MINUS)) ? tmp : 0;
			*flags = (!tmp) ? *flags | F_APP_PRECI : *flags & ~F_APP_PRECI;
		}
	}
}

void	field_width(t_printf *p, int *min_length)
{
	if (ft_strchr("123456789", *p->format))
	{
		*min_length = MAX(1, ft_atoi(p->format));
		while (ft_strchr("0123456789", *p->format))
			++p->format;
	}
}

void	precision(t_printf *p, int value)
{
	if (*p->format == '.')
	{
		value = ft_atoi(++p->format);
		p->precision = MAX(value, 0);
		while (ft_strchr("0123456789", *p->format))
			++p->format;
		p->f |= F_APP_PRECI;
	}
}

void	length_modifier(t_printf *p, short *lm)
{
	while (ft_strchr("hljzL", *p->format))
	{
		if (*p->format == 'h')
			*lm |= (*(p->format + 1) == 'h' && ++p->format) ? LM_SHORT2 : LM_SHORT;
		if (*p->format == 'l')
			*lm |= (*(p->format + 1) == 'l' && ++p->format) ? LM_LONG2 : LM_LONG;
		if (*p->format == 'j')
			*lm |= LM_INTMAX;
		if (*p->format == 'z')
			*lm |= LM_SIZE_T;
		++p->format;
	}
}
