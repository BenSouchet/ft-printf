/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 22:28:22 by bsouchet          #+#    #+#             */
/*   Updated: 2017/05/05 22:44:56 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	init__(unsigned long long **magic, void *cp,
									const unsigned char c)
{
	unsigned long long mask;

	mask = c;
	mask = (mask << 8) | mask;
	mask = (mask << 16) | mask;
	mask = ((mask << 16) << 16) | mask;
	*magic = (unsigned long long *)cp;
	return (mask);
}

static void					*test__(void *mem, const unsigned char c)
{
	unsigned char *cp;

	cp = (unsigned char *)mem;
	if (*cp == c)
		return ((void *)cp);
	if (*++cp == c)
		return ((void *)cp);
	if (*++cp == c)
		return ((void *)cp);
	if (*++cp == c)
		return ((void *)cp);
	if (*++cp == c)
		return ((void *)cp);
	if (*++cp == c)
		return ((void *)cp);
	if (*++cp == c)
		return ((void *)cp);
	if (*++cp == c)
		return ((void *)cp);
	return (NULL);
}

static void					*last_bytes__(unsigned char *cp, void *magic,
							const unsigned char c, size_t n)
{
	if (magic)
		cp = (unsigned char *)magic;
	while (n--)
	{
		if (*cp == c)
			return ((void *)cp);
		else
			++cp;
	}
	return (NULL);
}

void						*ft_memchr(const void *mem, const unsigned char c,
							size_t n)
{
	unsigned long long	mask;
	unsigned long long	*magic;
	unsigned char		*cp;

	cp = (unsigned char *)mem;
	magic = NULL;
	while (((sizeof(unsigned long long) - 1) & (unsigned long)cp) && n)
	{
		if (*cp++ == c)
			return (cp - 1);
		--n;
	}
	if (n >= 8)
	{
		mask = init__(&magic, cp, c);
		while (n >= 8)
		{
			if ((((*magic ^ mask) - LBITS) & HBITS))
				if ((cp = (unsigned char *)test__(magic, c)))
					return ((void *)cp);
			++magic;
			n -= 8;
		}
	}
	return (last_bytes__(cp, magic, c, n));
}
