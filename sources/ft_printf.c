/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:44 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/02 20:32:28 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...)
{
	t_printf	p;

	ft_bzero(&p, sizeof(p));
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			if (!p.format[1] || (p.format[1] == ' ' && (!p.format[2]
			|| (!p.format[3] && p.format[2] == 'h'))))
				break ;
			else if (++p.format && p.format[0] == '%' && ++p.len)
				buffer(&p, &p.format[0], 1);
			else
				parse_optionals(&p);
		}
		else if (++p.len)
			buffer(&p, &p.format[0], 1);
		++p.format;
	}
	write(p.fd, p.buff, p.buffer_index);
	va_end(p.ap);
	return (p.len);
}

static int		ft_strchr_index_2(char *s, int c, int i)
{
	while (s[++i])
		if (s[i] == c || s[i] == c + 32)
			return (i);
	return (-1);
}

char			*conversion_specifier(t_printf *p)
{
	if (ft_strchr("CDSUOB", *p->format))
		p->f |= LM_LONG;
	else if (*p->format == 'X')
		p->f |= F_UPCASE;
	if (ft_strchr("oOuUbBxX", *p->format))
		pf_putnb_base(ft_strchr_index_2(".b..ou..x", *p->format, -1) << 1, p);
	(ft_strchr("dDi", *p->format)) ? pf_putnb(p) : 0;
	(*p->format == 'c' || *p->format == 'C') ? pf_character(p) : 0;
	if (*p->format == 's')
		p->len += (p->f & LM_LONG || p->f & LM_LONG2) ?
			pf_wide_string(p) : pf_string(p);
	if (*p->format == 'S')
		p->len += pf_wide_string(p);
	(*p->format == 'p') ? print_pointer_address(p) : 0;
	(*p->format == 'n') ? *va_arg(p->ap, int *) = p->len : 0;
	(*p->format == 'm') ? p->len += ft_printf_putstr(strerror(errno), p) : 0;
	if (*p->format == 'f' || *p->format == 'F')
		(p->f & F_APP_PRECI && !p->precision) ? pf_putnb(p) : pf_putdouble(p);
	if (*p->format == '{')
		return (color(p));
	if (!ft_strchr("sSpdDibBoOuUxXcC%nmfF", *p->format))
		cs_not_found(p);
	return (p->format);
}

void			print_pointer_address(t_printf *p)
{
	int		sp_padding;
	void	*pointer;

	pointer = va_arg(p->ap, void *);
	p->f &= ~F_SHARP;
	p->min_length -= (p->f & F_ZERO ? 2 : 0);
	sp_padding = (p->printed > p->min_length - 3) ? 0 :
		p->min_length - 3 - p->printed;
	if (!(p->f & F_MINUS))
		while (sp_padding--)
			buffer(p, (p->f & F_ZERO) ? "0" : " ", 1);
	buffer(p, "0x", 2);
	itoa_base_printf((uintmax_t)pointer, 16, p);
	/*ft_putstr_free(s);*/
	if (p->f & F_MINUS)
		while (sp_padding--)
			buffer(p, (p->f & F_ZERO) ? "0" : " ", 1);
	p->len += MAX(p->printed + 2, p->min_length);
}

void			cs_not_found(t_printf *p)
{
	if (!(p->f & F_MINUS) && p->min_length > 1)
		ft_putnchar(p->min_length - 1, p->f & F_ZERO ? '0' : ' ');
	p->min_length > 1 ? p->len += p->min_length - 1 : 0;
	ft_putchar(*p->format);
	++p->len;
	if (p->f & F_MINUS && p->min_length > 1)
		ft_putnchar(p->min_length - 1, p->f & F_ZERO ? '0' : ' ');
}
