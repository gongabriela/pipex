/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:19:50 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/02/14 17:02:02 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_ft_putstr(char *s)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (write(1, "(null)", 6));
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	printf_ft_unsigned(unsigned int n)
{
	int	i;

	if (n == 2147483648)
		return (write (1, "2147483648", 10), 10);
	i = 0;
	if (n > 9)
		i += printf_ft_putnbr(n / 10);
	if (n <= 9)
		i = i + printf_ft_putchar(n + '0');
	else
		i = i + printf_ft_putchar(n % 10 + '0');
	return (i);
}

static int	ft_convert(const char *format, va_list args)
{
	if (*format == 'c')
		return (printf_ft_putchar(va_arg(args, int)));
	else if (*format == 's')
		return (printf_ft_putstr(va_arg(args, char *)));
	else if (*format == 'd' || *format == 'i')
		return (printf_ft_putnbr(va_arg(args, int)));
	else if (*format == '%')
		return (write(1, "%", 1), 1);
	else if (*format == 'u')
		return (printf_ft_unsigned(va_arg(args, unsigned int)));
	else if (*format == 'p')
		return (printf_ft_pointer(va_arg(args, void *)));
	else if (*format == 'x')
		return (printf_ft_hex(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (*format == 'X')
		return (printf_ft_hex(va_arg(args, unsigned int), "0123456789ABCDEF"));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		result;

	va_start(args, format);
	result = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			result += ft_convert(format, args);
		}
		else
			result += write(1, &(*format), 1);
		format++;
	}
	return (result);
}
