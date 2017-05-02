/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 18:37:46 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/02 20:29:25 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** -------------------------- External Headers ---------------------------------
*/

# include "../libft/libft.h"
# include <stdarg.h>
# include <errno.h>
# include <stdio.h>

/*
** -------------------------- Macros Definition --------------------------------
*/

# define MAX(a, b)		b & ((a - b) >> 31) | a & (~(a - b) >> 31)
# define MIN(a, b)		a & ((a - b) >> 31) | b & (~(a - b) >> 31)
# define ABS(a)			(a < 0) ? -a : a
# define COLOR(s,n)		ft_putstr(s), (p->format += n)

/*
** -------------------------- Colors Definition --------------------------------
*/

# define PF_RED			"\033[31m"
# define PF_GREEN		"\033[32m"
# define PF_YELLOW		"\033[33m"
# define PF_BLUE		"\033[34m"
# define PF_PURPLE		"\033[35m"
# define PF_CYAN		"\033[36m"
# define PF_EOC			"\033[36m"

/*
** --------------------------- Masks Definition --------------------------------
*/

# define F_SHARP		(1 << 0)
# define F_ZERO			(1 << 1)
# define F_PLUS			(1 << 2)
# define F_MINUS		(1 << 3)
# define F_SPACE		(1 << 4)
# define F_WILDCARD		(1 << 5)
# define F_MIN_LEN		(1 << 6)
# define F_APP_PRECI	(1 << 7)
# define F_UPCASE		(1 << 8)
# define LM_SHORT		(1 << 9)
# define LM_SHORT2		(1 << 10)
# define LM_LONG		(1 << 11)
# define LM_LONG2		(1 << 12)
# define LM_INTMAX		(1 << 13)
# define LM_SIZE_T		(1 << 14)


# define PF_BUF_SIZE	1024

/*
** ------------------------- Structure Definition ------------------------------
*/

typedef struct			s_printf
{
	int					len;
	short				f;
	int					min_length;
	int					precision;
	int					printed;
	int					fd;
	int					buffer_index;
	char				buff[PF_BUF_SIZE];
	char				*format;
	va_list				ap;
}						t_printf;

/*
** -----------------------------------------------------------------------------
** -------------------------------- Sources ------------------------------------
** -----------------------------------------------------------------------------
*/

int						ft_printf(const char *format, ...);
int						ft_printf_putchar(char c);

/*
** -------------------------- Parsing Functions --------------------------------
*/

void					parse_optionals(t_printf *p);
void					parse_flags(short *flags, t_printf *p);
void					field_width(t_printf *p, int *min_length);
void					precision(t_printf *p, int value);
void					length_modifier(t_printf *p, short *lm);

int						percent_char(t_printf *p);
char					*conversion_specifier(t_printf *p);
void					cs_not_found(t_printf *p);
void					ft_putnchar(int len, char c);

/*
** -------------------------- Numbers Functions -------------------------------
*/

void					pf_putnb(t_printf *p);
void					pf_putnb_base(int base, t_printf *p);
void					itoa_printf(intmax_t d, t_printf *p);
void					itoa_base_printf(uintmax_t d, int b, t_printf *p);
void					itoa_base_fill(uintmax_t tmp, int base, char *str,
						t_printf *p);

/*
** ---------------------- Strings & Chars Functions ----------------------------
*/

int						pf_string(t_printf *p);
int						pf_wide_string(t_printf *p);
void					pf_character(t_printf *p);
int						ft_printf_putstr(char *s, t_printf *p);
int						ft_printf_putwstr(wchar_t *s);

/*
** --------------------------- Bonus Functions ----------------------------------
*/

void					print_pointer_address(t_printf *p);
char					*color(t_printf *p);
void					pf_putdouble(t_printf *p);
char					*pf_ldtoa(double n, t_printf *p);
void					ldtoa_fill(double n, char *s, t_printf *p);

/*
** --------------------------- Misc Functions ----------------------------------
*/

int						ft_strchr_index(char *s, int c);

/*
** --------------------------- Buffer Functions --------------------------------
*/

void					buffer(t_printf *p, void *new_elem, size_t size);
void					buffer_flush(t_printf *p);

#endif
