/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 19:23:20 by bsouchet          #+#    #+#             */
/*   Updated: 2017/05/05 19:50:27 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <locale.h>

/*
** +------------------------------ Bonus Done ---------------------------------+
** |                                                                           |
** |                                                                           |
** | 1. * Widlcard Lenght Modifier (Check moulitest for the tests)             |
** |                                                                           |
** | 2. %f & %F flags (Decimal floating point) (Check moulitest for the tests) |
** |                                                                           |
** | 3. %n The argument shall be a pointer to an integer into which is written |
** |    the number of bytes written to the output so far by this call to one   |
** |    of the printf() functions. No argument is converted.                   |
** |                                                                           |
** | 4. %m Prints the string corresponding to the error code in errno.         |
** |    Equivalent to: dprintf(stderr, "error: %s\n", strerror(errno));        |
** |                                                                           |
** | 5. {clr} Color gestion of the output ( {cyan}, {red}, {green}, {eoc},...) |
** |                                                                           |
** +---------------------------------------------------------------------------+
*/

int		main(void)
{
	int val;

	ft_printf("\n------------ Bonus tests -----------\n");
	ft_printf("------------------------------------\n");
	ft_printf("\n- - - - - - - %%n Tests - - - - - - -\n\n");
	ft_printf("Original printf (<stdio.h>)  :\n");
	printf("Hello World %n\n", &val);
	printf("Characters printed so far = %d\n\n", val);
	ft_printf("My own Printf (ft_printf)    :\n");
	ft_printf("Hello World %n\n", &val);
	ft_printf("Characters printed so far = %d\n\n", val);
	ft_printf("\n");
	ft_printf("Original printf (<stdio.h>)  :\n");
	printf("test %nusing %%n flag\n", &val);
	printf("val = %d\n\n", val);
	ft_printf("My own Printf (ft_printf)    :\n");
	ft_printf("test %nusing %%n flag\n", &val);
	ft_printf("val = %d\n\n", val);
	ft_printf("\n- - - - - - - %%m Tests - - - - - - -\n\n");
	open("420_blaze_it.42", O_RDONLY);
	ft_printf("Original dprintf (<stdio.h>) :\n");
	val = dprintf(2, "error: %s\n", strerror(errno));
	ft_printf("returned val = %d\n\n", val);
	ft_printf("My own dprintf (ft_dprintf)  :\n");
	val = ft_dprintf(2, "error: %s\n", strerror(errno));
	ft_printf("returned val = %d\n\n", val);
	ft_printf("\n");
	open("/Users/bsouchet/OMGBRO.lol", O_RDONLY);
	ft_printf("Original dprintf (<stdio.h>) :\n");
	val = dprintf(2, "error: %s\n", strerror(errno));
	ft_printf("returned val = %d\n\n", val);
	ft_printf("My own dprintf (ft_dprintf)  :\n");
	val = ft_dprintf(2, "error: %s\n", strerror(errno));
	ft_printf("returned val = %d\n\n", val);
	ft_printf("\n");
	open("/Users/bsouchet/", O_WRONLY);
	ft_printf("Original dprintf (<stdio.h>) :\n");
	val = dprintf(2, "error: %s\n", strerror(errno));
	ft_printf("returned val = %d\n\n", val);
	ft_printf("My own dprintf (ft_dprintf)  :\n");
	val = ft_dprintf(2, "error: %s\n", strerror(errno));
	ft_printf("returned val = %d\n\n", val);
	ft_printf("\n- - - - - - Colors Tests - - - - - -\n\n");
	ft_printf("Original printf (<stdio.h>) :\n");
	printf(PF_RED "OMG BrO'!" PF_GREEN " 420 Blaze iT" PF_YELLOW " in your Face!\n" PF_EOC);
	printf(PF_BLUE "O BABY A TRIPLE!" PF_PURPLE " FATALITY!" PF_CYAN " U MAD BRO\n" PF_EOC);
	ft_printf("\033[0m- Test after reset of basic color! -\n\n");
	ft_printf("Same with my printf (ft_printf) :\n");
	ft_printf(PF_RED "OMG BrO'!" PF_GREEN " 420 Blaze iT" PF_YELLOW " in your Face!\n" PF_EOC);
	ft_printf(PF_BLUE "O BABY A TRIPLE!" PF_PURPLE " FATALITY!" PF_CYAN " U MAD BRO\n" PF_EOC);
	ft_printf("- Test after reset of basic color! -\n\n");
	ft_printf("My own printf (ft_printf) :\n");
	ft_printf("%{red}OMG BrO'!%{eoc} %{green}420 Blaze iT%{eoc} %{yellow}in your Face!%{eoc}\n");
	ft_printf("%{blue}O BABY A TRIPLE!%{eoc} %{purple}FATALITY!%{eoc} %{cyan}U MAD BRO%{eoc}\n");
	ft_printf("- Test after reset of basic color! -\n\n");
	return (1);
}
