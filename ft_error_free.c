/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:51:48 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/26 19:51:48 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_lst(t_pipex **head)
{
	t_pipex	*temp;
	t_pipex	*next;
	int		i;

	temp = *head;
	while (temp != NULL)
	{
		next = temp->next;
		if (temp->commands != NULL)
		{
			i = 0;
			while (temp->commands[i] != NULL)
				free(temp->commands[i++]);
			free(temp->commands);
		}
		if (temp->path != NULL)
			free(temp->path);
		if (temp->file != NULL)
			free(temp->file);
		free(temp);
		temp = next;
	}
	*head = NULL;
}

void	free_d_array(char **d_array)
{
	int	i;

	i = 0;
	while (d_array[i] != NULL)
		free(d_array[i++]);
	free(d_array);
}

void	improved_error(t_pipex **head, char *strerror, char *args)
{
	char	*full_err;

	if (args != NULL)
	{
		if (ft_isspace(args[0]) == 1 && args[1] == '\0')
			full_err = ft_strjoin(ft_print_isspace(args[0]), strerror);
		else
			full_err = ft_strjoin(strerror, args);
		ft_putendl_fd(full_err, 2);
		free(full_err);
	}
	else if (strerror != NULL)
		ft_putendl_fd(strerror, 2);
	if (*head != NULL)
		free_lst(head);
	exit(EXIT_FAILURE);
}

char	*ft_print_isspace(char c)
{
	if (c == '\t')
		return ("\\t");
	else if (c == ' ')
		return (" ");
	else if (c == '\n')
		return ("\\n");
	else if (c == '\v')
		return ("\\v");
	else if (c == '\f')
		return ("\\f");
	else if (c == '\r')
		return ("\\r");
	return (NULL);
}
