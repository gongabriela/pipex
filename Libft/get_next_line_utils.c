/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:18:58 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/02/03 09:47:42 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_ft_strjoin(char *buffer, char *temp)
{
	char	*conc;
	int		i;
	int		j;

	conc = ft_calloc((ft_strlen(buffer) + ft_strlen(temp) + 1), sizeof(char));
	if (conc == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (buffer[j] != '\0')
		conc[i++] = buffer[j++];
	j = 0;
	while (temp[j] != '\0')
		conc[i++] = temp[j++];
	free(buffer);
	free(temp);
	return (conc);
}
