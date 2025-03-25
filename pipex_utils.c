/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:52 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/25 16:18:23 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_list(t_pipex	**head)
{
	t_pipex	*node;
	int		i;

	i = 0;
	while (i++ < 2)
	{
		node = (t_pipex *)malloc(sizeof(t_pipex));
		if (node == NULL)
		{
			if (*head != NULL)
				free(*head);
			exit(1);
		}
		if (*head == NULL)
			*head = node;
		else
			(*head)->next = node;
		node->commands = NULL;
		node->path = NULL;
		node->file = NULL;
		node->next = NULL;
	}
}

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

int	parsing_args(char **argv, t_pipex *head)
{
	int		i;

	i = 1;
	while (i <= 4)
	{
		if (access(argv[i], R_OK) == -1 && i == 1)
			return (ft_printf("Error: %s: ./%s\n", strerror(errno),
					argv[i]), -1);
		else
			head->file = ft_strdup(argv[i]);
		i++;
		while (i <= 3)
		{
			head->commands = ft_split(argv[i], ' ');
			if (head->commands == NULL)
				return (-1);
			head->path = get_path(head->commands[0]);
			if (head->path == NULL)
				return (-1);
			if (i == 2)
				head = head->next;
			i++;
		}
	}
	return (0);
}

void	free_d_array(char **d_array)
{
	int	i;

	i = 0;
	while (d_array[i] != NULL)
		free(d_array[i++]);
	free(d_array);
}

char	*get_path(char *command)
{
	char	**paths;
	char	*command_path;
	int		i;

	if (command == NULL)
		return (NULL);
	paths = ft_split("/bin/ /usr/bin/ /usr/local/bin/", ' ');
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		command_path = ft_strjoin(paths[i++], command);
		if (command_path == NULL || (access(command_path, X_OK) == -1 && i == 3)
			|| (access(command_path, X_OK) == 0))
			free_d_array(paths);
		if (access(command_path, X_OK) == -1)
			free(command_path);
		else
			break ;
	}
	if (i == 3)
		return (ft_printf("Error: command not found: %s\n", command), NULL);
	return (command_path);
}
