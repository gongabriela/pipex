/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:35:11 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/02/14 17:02:04 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_ft_hex(unsigned int n, char *base)
{
	int	i;

	i = 0;
	if (n >= 16)
		i += printf_ft_hex(n / 16, base);
	i += write(1, &base[n % 16], 1);
	return (i);
}

static int	printf_ft_hexp(unsigned long long n, char *base)
{
	int	i;

	i = 0;
	if (n >= 16)
		i += printf_ft_hexp(n / 16, base);
	i += write(1, &base[n % 16], 1);
	return (i);
}

int	printf_ft_pointer(void *p)
{
	if (p == NULL)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	return (2 + printf_ft_hexp((unsigned long long)p, "0123456789abcdef"));
}

int	printf_ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	printf_ft_putnbr(int n)
{
	int	i;
	int	nbr;

	if (n == -2147483648)
		return (write (1, "-2147483648", 11), 11);
	if (n < 0)
	{
		nbr = -n;
		write (1, "-", 1);
	}
	else
		nbr = n;
	i = 0;
	if (nbr > 9)
		i += printf_ft_putnbr(nbr / 10);
	if (nbr <= 9)
		i = i + printf_ft_putchar(nbr + '0');
	else
		i = i + printf_ft_putchar(nbr % 10 + '0');
	if (nbr == -n && n < 0)
		return (i + 1);
	return (i);
}
