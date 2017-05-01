/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 19:31:22 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/01 20:15:04 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_wide_string(t_printf *p)
{
	wchar_t		*s;
	int			wlen;
	int			sp_padding;
	int			charlen;

	if (!(s = va_arg(p->ap, wchar_t *)))
		return (ft_printf_putwstr((wchar_t *)s));
	wlen = (int)(ft_wstrlen((unsigned *)s));
	(p->f & F_APP_PRECI) ? wlen = MIN(p->precision, wlen) : 0;
	sp_padding = MAX(p->min_length - wlen + (p->precision > 1 ? 1 : 0), 0);
	p->f = (p->min_length > p->precision) ? p->f & ~F_APP_PRECI : p->f | F_APP_PRECI;
	if (!(p->f & F_MINUS))
		ft_putnchar(sp_padding, (p->f & F_ZERO) ? '0' : ' ');
	charlen = 0;
	while (*s && (wlen -= charlen) > 0)
	{
		charlen = ft_putwchar(*s, wlen);
		p->printed += charlen;
		++s;
	}
	if (p->f & F_MINUS)
		ft_putnchar(sp_padding, (p->f & F_ZERO) ? '0' : ' ');
	p->printed += MAX(sp_padding, 0);
	return (p->printed);
}

int		pf_string(t_printf *p)
{
	unsigned	*s;
	int			len;
	int			sp_padding;

	if (!(s = va_arg(p->ap, unsigned*)))
		return (ft_printf_putstr((char *)s, p));
	len = (int)(ft_strlen((char*)s));
	(p->f & F_APP_PRECI) ? len = MIN(p->precision, len) : 0;
	sp_padding = (p->min_length - len) > 0 ? (p->min_length - len) : 0;
	if (!(p->f & F_MINUS))
		ft_putnchar(sp_padding, (p->f & F_ZERO) ? '0' : ' ');
	while ((char)*s && len--)
	{
		ft_putchar((char)(*s));
		++p->printed;
		s = (unsigned *)((char*)s + 1);
	}
	if (p->f & F_MINUS)
		ft_putnchar(sp_padding, ' ');
	p->printed += MAX(sp_padding, 0);
	return (p->printed);
}

int		ft_printf_putstr(char *s, t_printf *p)
{
	if (!s)
	{
		(!(p->f & F_ZERO)) ? ft_putstr("(null)") :
			ft_putnchar(p->min_length, '0');
		return (!(p->f & F_ZERO) ? 6 : p->min_length);
	}
	ft_putstr(s);
	return ((int)ft_strlen(s));
}

int		ft_printf_putwstr(wchar_t *s)
{
	(s == L'\0') ? ft_putstr("(null)") : ft_putwstr(s);
	return (!s ? 6 : (int)ft_wstrlen((unsigned *)s));
}

void	ft_putnchar(int len, char c)
{
	static char	test[4096];
	const int	tmp = len;

	while (len--)
		*(test + len) = c;
	write(1, test, tmp);
}
