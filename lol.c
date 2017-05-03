#include <stdio.h>
#include "include/ft_printf.h"
#include <locale.h>

int		main(void)
{
	int i;

	setlocale(LC_ALL, "");
	printf("%d|\n", printf("%15.4S|\n", L"我是一只猫。"));
	printf("%d|\n", ft_printf("%15.4S|\n", L"我是一只猫。"));

	printf("%4.1S\n", L"Jambon");
	ft_printf("%4.1S\n", L"Jambon");
	return (1);
}
