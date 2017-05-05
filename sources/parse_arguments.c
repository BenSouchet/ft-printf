/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:36:51 by bsouchet          #+#    #+#             */
/*   Updated: 2017/05/05 19:42:06 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_flags(t_printf *p)
{
	short	n;

	while ((n = ft_strchri("# +-0*", p->format[0], -1)) > -1 && ++p->format)
		p->f |= (1 << n);
	((p->f & F_MINUS) && !(p->f & F_WILDCARD)) ? p->f &= ~F_ZERO : 0;
	(p->f & F_PLUS) ? p->f &= ~F_SPACE : 0;
	if (p->f & F_WILDCARD)
	{
		p->f &= ~F_WILDCARD;
		if ((n = (int)va_arg(p->ap, int)) < 0)
		{
			p->f |= F_MINUS;
			n = -n;
		}
		else
			p->f &= ~F_MINUS;
		if (!(p->f & F_APP_PRECI))
			p->min_length = n;
		else
		{
			p->precision = (!(p->f & F_MINUS)) ? n : 0;
			p->f = (!n) ? p->f | F_APP_PRECI : p->f & ~F_APP_PRECI;
		}
	}
}

static void	field_width_precision(t_printf *p)
{
	if (48 < p->format[0] && p->format[0] < 58)
	{
		p->min_length = MAX(1, ft_atoi(p->format));
		while (47 < p->format[0] && p->format[0] < 58)
			++p->format;
	}
	if (p->format[0] == '.' && ++p->format)
	{
		p->precision = MAX(ft_atoi(p->format), 0);
		while (47 < p->format[0] && p->format[0] < 58)
			++p->format;
		p->f |= F_APP_PRECI;
	}
}

static void	conversion_specifier(t_printf *p)
{
	//p->printed = 0;
	p->c = *p->format;
	if (p->c == 's')
		(p->f & F_LONG || p->f & F_LONG2) ? pf_putwstr(p) : pf_putstr(p);
	else if (ft_strchr("dDi", p->c))
		pf_putnb(p);
	else if (p->c == 'f' || p->c == 'F')
		(p->f & F_APP_PRECI && !p->precision) ? pf_putnb(p) : pf_putdouble(p);
	else if (ft_strchr("oOuUbBxX", p->c))
		pf_putnb_base(ft_strchri_lu(".b..ou..x", p->c, -1) << 1, p);
	else if (p->c == 'c' || p->c == 'C')
		pf_character(p, va_arg(p->ap, unsigned));
	else if (p->c == 'S')
		pf_putwstr(p);
	else if (p->c == 'p')
		print_pointer_address(p);
	else if (p->c == 'n')
		*va_arg(p->ap, int *) = p->len;
	else if (p->c == 'm')
		ft_printf_putstr(STRERR(errno), p);
	else if (p->c == '{')
		color(p);
	else
		cs_not_found(p);
}

void		parse_optionals(t_printf *p)
{
	p->f = 0;
	p->min_length = 0;
	p->precision = 1;
	parse_flags(p);
	field_width_precision(p);
	while (ft_strchr("hljzL", p->format[0]))
	{
		if (p->format[0] == 'h')
			p->f |= (p->format[1] == 'h' && ++p->format) ? F_SHORT2 : F_SHORT;
		else if (p->format[0] == 'l')
			p->f |= (p->format[1] == 'l' && ++p->format) ? F_LONG2 : F_LONG;
		else if (p->format[0] == 'j')
			p->f |= F_INTMAX;
		else if (p->format[0] == 'z')
			p->f |= F_SIZE_T;
		++p->format;
	}
	parse_flags(p);
	(p->f & F_PLUS) ? p->f &= ~F_SPACE : 0;
	if (ft_strchr("CDSUOB", p->format[0]))
		p->f |= F_LONG;
	else if (p->format[0] == 'X')
		p->f |= F_UPCASE;
	conversion_specifier(p);
}

void		cs_not_found(t_printf *p)
{
	if ((p->padding = p->min_length - 1) > 0)
	{
		padding(p, 0);
		buffer(p, p->format, 1);
		padding(p, 1);
	}
	else
		buffer(p, p->format, 1);
}
