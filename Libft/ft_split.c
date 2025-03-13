/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:50:18 by ggoncalv          #+#    #+#             */
/*   Updated: 2024/11/14 16:01:36 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			j++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (j);
}

static char	**ft_free(char **split, int b)
{
	if (split[b] == NULL)
	{
		while (b >= 0)
			free(split[b--]);
		free(split);
	}
	return (NULL);
}

static void	init_var(int *i, int *a, int *b)
{
	*i = 0;
	*a = 0;
	*b = 0;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		a;
	int		b;
	char	**split;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	init_var(&i, &a, &b);
	while (s[i] != '\0' && b < count_words(s, c))
	{
		while (s[i] == c)
			i++;
		a = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		split[b] = ft_substr(s, a, i - a);
		if (split[b] == NULL)
			return (ft_free(split, b));
		b++;
	}
	split[b] = NULL;
	return (split);
}
