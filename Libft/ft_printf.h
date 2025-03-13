/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:17:44 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/01/25 14:40:07 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>
# include "libft.h"

int	ft_printf(const char *format, ...);
int	printf_ft_putchar(char c);
int	printf_ft_putstr(char *s);
int	printf_ft_putnbr(int n);
int	printf_ft_unsigned(unsigned int n);
int	printf_ft_hex(unsigned int n, char *base);
int	printf_ft_pointer(void *p);

#endif
