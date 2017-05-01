/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 20:03:13 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/01 20:14:53 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putnb(t_printf *p)
{
	intmax_t	n;
	int			sp_padding;

	if (p->f & LM_LONG || p->f & LM_LONG2)
		n = (p->f & LM_LONG2) ? ((intmax_t)va_arg(p->ap, long long)) :
			((intmax_t)va_arg(p->ap, long));
	else if (p->f & LM_SHORT || p->f & LM_SHORT2)
		n = (p->f & LM_SHORT2) ? (intmax_t)((char)va_arg(p->ap, int)) :
			(intmax_t)((short)va_arg(p->ap, int));
	else if (p->f & LM_INTMAX)
		n = (va_arg(p->ap, intmax_t));
	else if (p->f & LM_SIZE_T)
		n = ((intmax_t)va_arg(p->ap, ssize_t));
	else
		n = ((intmax_t)va_arg(p->ap, int));
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	itoa_printf(n, p);
	sp_padding = (p->printed > p->min_length) ? 0 : p->min_length - p->printed;
	(!(p->f & F_ZERO) && !(p->f & F_MINUS)) ? ft_putnchar(sp_padding, ' ') : 0;
	p->f & F_MINUS ? ft_putnchar(sp_padding, ' ') : 0;
	p->len += MAX(p->printed, p->min_length);
}

void	pf_putnb_base(int base, t_printf *p)
{
	uintmax_t	n;
	int			sp_padding;

	if (p->f & LM_LONG || p->f & LM_LONG2)
		n = (p->f & LM_LONG2) ? ((intmax_t)va_arg(p->ap, unsigned long long)) :
			((intmax_t)va_arg(p->ap, unsigned long));
	else if (p->f & LM_SHORT || p->f & LM_SHORT2)
		n = (p->f & LM_SHORT2) ? (uintmax_t)((unsigned char)va_arg(p->ap, int)) :
			(uintmax_t)((unsigned short)va_arg(p->ap, int));
	else if (p->f & LM_INTMAX)
		n = (va_arg(p->ap, uintmax_t));
	else if (p->f & LM_SIZE_T)
		n = ((uintmax_t)va_arg(p->ap, size_t));
	else
		n = (uintmax_t)va_arg(p->ap, unsigned int);		
	itoa_base_printf(n, base, p);
	sp_padding = MAX(0, (p->min_length - p->printed));
	(!(p->f & F_ZERO) && !(p->f & F_MINUS)) ? ft_putnchar(sp_padding, ' ') : 0;
	p->f & F_MINUS ? ft_putnchar(sp_padding, ' ') : 0;
	p->len += MAX(p->printed, p->min_length);
}

void	itoa_printf(intmax_t n, t_printf *p)
{
	char		s[PF_BUF_SIZE];
	int			len;
	uintmax_t	tmp;

	len = 0;
	tmp = ABS(n);
	while (tmp)
	{
		tmp /= 10;
		++len;
	}
	if ((n < 0 || p->f & F_PLUS || p->f & F_SPACE) && p->f & F_ZERO)
		--p->precision;
	p->printed = MAX(len, p->precision);
	if (n < 0 || p->f & F_PLUS || p->f & F_SPACE)
		++p->printed;
	tmp = ABS(n);
	itoa_base_fill(tmp, 10, s, p);
	(p->f & F_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & F_PLUS && n >= 0) ? s[0] = '+' : 0;
	buffer(p, s, p->printed + 1);
}

void	itoa_base_printf(uintmax_t n, int b, t_printf *p)
{
	uintmax_t	tmp;
	char		s[PF_BUF_SIZE];
	int			len;
	int			ext;

	len = 0;
	tmp = n;
	while (tmp)
	{
		tmp /= b;
		++len;
	}
	if (p->f & F_ZERO)
		p->precision = p->min_length;
	ext = (len >= p->precision) ? 0 : 1;
	p->printed = MAX(p->precision, len);
	((p->f & F_SHARP) && b == 8 && !ext) ? p->printed += 1 : 0;
	((p->f & F_SHARP) && b == 16 && n && !(p->f & F_ZERO)) ? p->printed += 2 : 0;
	itoa_base_fill(n, b, s, p);
	((p->f & F_SHARP) && ((b == 8 && !ext) || (b == 16 && n))) ? s[0] = '0' : 0;
	if ((p->f & F_SHARP) && b == 16 && n)
		s[1] = 'x' - ((p->f & F_UPCASE) << 5);
	buffer(p, s, p->printed + 1);
}

void	itoa_base_fill(uintmax_t tmp, int b, char s[PF_BUF_SIZE], t_printf *p)
{
	int		letter;
	int		len;

	len = p->printed;
	letter = 'a' - 10 - ((p->f & F_UPCASE) << 5);
	s[len] = '\0';
	while (len--)
	{
		s[len] = tmp % b + ((tmp % b < 10) ? '0' : letter);
		tmp /= b;
	}
	(p->f & F_APP_PRECI && p->f & F_ZERO) ? s[0] = ' ' : 0;
}
