/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:23:53 by ggoncalv          #+#    #+#             */
/*   Updated: 2024/11/14 16:26:51 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	size;

	if (n == -2147483648)
		return (11);
	size = 0;
	if (n < 0)
	{
		n = -n;
		size++;
	}
	if (n == 0)
		size++;
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static char	*putnbr(char *str, int n, int size)
{
	long	nbr;

	str[size] = '\0';
	size--;
	str[0] = '0';
	nbr = 0;
	if (n < 0)
	{
		nbr -= n;
		str[0] = '-';
	}
	else
		nbr = n;
	while (nbr > 0)
	{
		str[size] = nbr % 10 + 48;
		nbr = nbr / 10;
		size--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;

	size = count_size(n);
	str = malloc(size + 1 * sizeof(char));
	if (str == NULL)
		return (NULL);
	str = putnbr(str, n, size);
	return (str);
}
