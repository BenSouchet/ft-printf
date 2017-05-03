/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 20:03:13 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/03 17:12:52 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** ft_putnb but for printf (returns len and adds padding)
*/

void	pf_putnb(t_printf *p)
{
	intmax_t	n;

	if (p->f & F_LONG || p->f & F_LONG2)
		n = (p->f & F_LONG2) ? ((intmax_t)va_arg(p->ap, long long)) :
			((intmax_t)va_arg(p->ap, long));
	else if (p->f & F_SHORT || p->f & F_SHORT2)
		n = (p->f & F_SHORT2) ? (intmax_t)((char)va_arg(p->ap, int)) :
			(intmax_t)((short)va_arg(p->ap, int));
	else if (p->f & F_INTMAX)
		n = (va_arg(p->ap, intmax_t));
	else if (p->f & F_SIZE_T)
		n = ((intmax_t)va_arg(p->ap, ssize_t));
	else
		n = ((intmax_t)va_arg(p->ap, int));
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	itoa_printf(n, p);
}

/*
** put number base will returns len and add the padding
** a base number is considered as unsigned by printf
** printf only handle binary, octal and hex.
*/

void	pf_putnb_base(int base, t_printf *p)
{
	uintmax_t	n;

	if (p->f & F_LONG || p->f & F_LONG2)
		n = (p->f & F_LONG2) ? ((intmax_t)va_arg(p->ap, unsigned long long)) :
			((intmax_t)va_arg(p->ap, unsigned long));
	else if (p->f & F_SHORT || p->f & F_SHORT2)
		n = (p->f & F_SHORT2) ? (uintmax_t)((unsigned char)va_arg(p->ap, int))
			: (uintmax_t)((unsigned short)va_arg(p->ap, int));
	else if (p->f & F_INTMAX)
		n = (va_arg(p->ap, uintmax_t));
	else if (p->f & F_SIZE_T)
		n = ((uintmax_t)va_arg(p->ap, size_t));
	else
		n = (uintmax_t)va_arg(p->ap, unsigned int);
	itoa_base_printf(n, base, p);
}

/*
** transforms int n into char *s
*/

void	itoa_printf(intmax_t n, t_printf *p)
{
	char		s[21];
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
	p->padding = (p->printed > p->min_length) ? 0 : p->min_length - p->printed;
	padding(p, 0);
	tmp = ABS(n);
	itoa_base_fill(tmp, 10, s, p);
	(p->f & F_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & F_PLUS && n >= 0) ? s[0] = '+' : 0;
	buffer(p, s, p->printed);
	padding(p, 1);
}

/*
** same as above for any base
*/

void	itoa_base_printf(uintmax_t n, int b, t_printf *p)
{
	uintmax_t	tmp;
	char		s[21];
	int			ext;

	p->printed = 0;
	tmp = n;
	while (tmp && ++p->printed)
		tmp /= b;
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	ext = (p->printed >= p->precision) ? 0 : 1;
	p->printed = MAX(p->precision, p->printed);
	((p->f & F_SHARP) && b == 8 && !ext) ? --p->min_length : 0;
	((p->f & F_SHARP) && b == 16 && !(p->f & F_ZERO)) ? p->min_length -= 2 : 0;
	p->padding = MAX(0, (p->min_length - p->printed));
	padding(p, 0);
	if ((n || (p->f & F_POINTER))
		&& (p->f & F_SHARP) && ((b == 8 && !ext) || (b == 16)))
		buffer(p, "0", 1);
	if ((n || (p->f & F_POINTER)) && (p->f & F_SHARP) && b == 16)
		buffer(p, (p->f & F_UPCASE) ? "X" : "x", 1);
	itoa_base_fill(n, b, s, p);
	buffer(p, s, p->printed);
	padding(p, 1);
}

/*
** variable letter only works for base 16 in printf
** letter = 'a' - 10 - (p->f & F_LONG) is to get directly the
** letter with caplock if X was parsed.
*/

void	itoa_base_fill(uintmax_t tmp, int b, char s[PF_BUF_SIZE], t_printf *p)
{
	int		len;

	len = p->printed;
	p->c = 'a' - 10 - ((p->f & F_UPCASE) >> 1);
	while (len--)
	{
		s[len] = tmp % b + ((tmp % b < 10) ? '0' : p->c);
		tmp /= b;
	}
	(p->f & F_APP_PRECI && p->f & F_ZERO) ? s[0] = ' ' : 0;
}
