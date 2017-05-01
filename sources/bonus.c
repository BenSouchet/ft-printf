/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 15:55:33 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/01 20:14:38 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strchr_index(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

char	*color(t_printf *p)
{
	p->printed = 5;
	if (!ft_strncmp(p->format, "{red}", ft_strlen("{red}")))
		COLOR(PF_RED, 5);
	else if (!ft_strncmp(p->format, "{green}", ft_strlen("{green}")))
		COLOR(PF_GREEN, 7);
	else if (!ft_strncmp(p->format, "{yellow}", ft_strlen("{yellow}")))
		COLOR(PF_YELLOW, 8);
	else if (!ft_strncmp(p->format, "{blue}", ft_strlen("{blue}")))
		COLOR(PF_BLUE, 6);
	else if (!ft_strncmp(p->format, "{purple}", ft_strlen("{purple}")))
		COLOR(PF_PURPLE, 8);
	else if (!ft_strncmp(p->format, "{cyan}", ft_strlen("{cyan}")))
		COLOR(PF_CYAN, 6);
	else if (!ft_strncmp(p->format, "{eoc}", ft_strlen("{eoc}")))
		COLOR(PF_EOC, 5);
	else
		p->printed = 0;
	p->len += p->printed;
	return (p->format - 1);
}

void	pf_putdouble(t_printf *p)
{
	char		*s;
	double		n;

	n = (double)va_arg(p->ap, double);
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	s = pf_ldtoa(n, p);
	/*ft_putstr_free(s);*/
	p->len += MAX(p->printed, p->min_length);
}

char	*pf_ldtoa(double n, t_printf *p)
{
	long		tmp;
	char		*s;
	int			len;
	
	if (!(p->f & F_APP_PRECI))
		p->precision = 6;
	len = (p->precision > 0) ? 1 : 0;
	tmp = (long)(ABS(n));
	while (tmp)
	{
		tmp /= 10;
		++len;
	}
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	p->printed = p->precision + len + ((n < 0) ? 1 : 0);
	if (!(s = (char*)malloc(sizeof(char) * (p->printed + 1))))
		return (NULL);
	ldtoa_fill(n, s, p);
	(p->f & F_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & F_PLUS && n >= 0) ? s[0] = '+' : 0;
	return (s);
}

void	ldtoa_fill(double n, char *s, t_printf *p)
{
	int		len;
	int		accuracy;
	double	decimal;
	long	value;

	decimal = ABS(n);
	decimal = (decimal - (long)(ABS(n))) * ft_pow(10, p->precision + 1);
	decimal = ((long)decimal % 10 > 4) ? (decimal) / 10 + 1 : decimal / 10;
	len = p->printed - 1 - p->precision;
	accuracy = p->printed - 1 - len;
	s[p->printed] = '\0';
	value = (int)decimal;
	while (accuracy--)
	{
		s[len + accuracy + 1] = value % 10 + '0';
		value /= 10;
	}
	(p->precision > 0) ? s[len] = '.' : 0;
	value = (long)(ABS(n));
	while (len--)
	{
		s[len] = value % 10 + '0';
		value /= 10;
	}
	(p->f & F_APP_PRECI && p->f & F_ZERO) ? s[0] = ' ' : 0;
}
