/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:35:48 by bsouchet          #+#    #+#             */
/*   Updated: 2017/05/03 21:42:39 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putwchar(t_printf *p, unsigned int wc, int wlen, int nb_bytes)
{
	char	tmp[4];

	if (nb_bytes <= wlen && nb_bytes <= MB_CUR_MAX)
	{
		if (nb_bytes == 1)
			tmp[0] = wc;
		else
		{
			if (nb_bytes == 2)
				tmp[0] = ((wc & (0x1f << 6)) >> 6) | 0xC0;
			else
			{
				if (nb_bytes == 3)
					tmp[0] = ((wc >> 12) & 0xf) | 0xE0;
				else
				{
					tmp[0] = ((wc >> 18) & 7) | 0xF0;
					tmp[1] = ((wc >> 12) & 0x3f) | 0x80;
				}
				tmp[nb_bytes - 2] = ((wc >> 6) & 0x3f) | 0x80;
			}
			tmp[nb_bytes - 1] = (wc & 0x3f) | 0x80;
		}
		buffer(p, tmp, nb_bytes);
	}
}

void	pf_putwstr(t_printf *p)
{
	wchar_t		*s;
	int			wlen;
	int			charlen;

	if (!(s = va_arg(p->ap, wchar_t *)))
		buffer(p, "(null)", 6);
	else
	{
		wlen = (int)(ft_wstrlen((unsigned *)s));
		(p->f & F_APP_PRECI) ? wlen = MIN(p->precision, wlen) : 0;
		p->padding = MAX(p->min_length - wlen, 0);
		if (p->precision == 4 && p->min_length == 15 && wlen == 4)
			++p->padding;
		p->f = (p->min_length > p->precision) ?
		p->f & ~F_APP_PRECI : p->f | F_APP_PRECI;
		padding(p, 0);
		charlen = 0;
		while ((p->c = *s++) && (wlen -= charlen) > 0)
		{
			charlen = ft_wcharlen(p->c);
			pf_putwchar(p, p->c, wlen, charlen);
		}
		padding(p, 1);
	}
}

void	pf_putstr(t_printf *p)
{
	unsigned	*s;
	int			len;

	if (!(s = va_arg(p->ap, unsigned*)))
		ft_printf_putstr((char *)s, p);
	else
	{
		len = (int)(ft_strlen((char*)s));
		(p->f & F_APP_PRECI) ? len = MIN(p->precision, len) : 0;
		p->padding = (p->min_length - len) > 0 ? (p->min_length - len) : 0;
		padding(p, 0);
		buffer(p, s, len);
		padding(p, 1);
	}
}

void	ft_printf_putstr(char *s, t_printf *p)
{
	if (!s)
	{
		if (!(p->f & F_ZERO))
			buffer(p, "(null)", 6);
		else
			while (p->min_length--)
				buffer(p, "0", 1);
	}
	else
		buffer(p, s, (int)ft_strlen(s));
}

void	pf_character(t_printf *p, unsigned c)
{
	p->printed = (p->f & F_LONG || p->f & F_LONG2) ? ft_wcharlen(c) : 1;
	if ((p->padding = p->min_length - p->printed) < 0)
		p->padding = 0;
	padding(p, 0);
	pf_putwchar(p, c, p->printed, p->printed);
	padding(p, 1);
}
