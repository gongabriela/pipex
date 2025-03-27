/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:52 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/27 14:48:58 by ggoncalv         ###   ########.fr       */
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

void	parse_file(t_pipex **head, char *file, int file_id)
{
	int	ret;

	if (file_id == 1)
		ret = access(file, R_OK);
	else
		ret = access(file, W_OK);
	if (ret == -1)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("zsh: ", 2);
			improved_error(head, "no such file or directory: ", file);
		}
		else if (errno == EACCES)
		{
			ft_putstr_fd("zsh: ", 2);
			improved_error(head, "permission denied: ", file);
		}
		else
			perror("pipex");
	}
	(*head)->file = ft_strdup(file);
}

void	parsing_args(char **argv, t_pipex **head)
{
	t_pipex	*temp;
	int		i;

	temp = *head;
	i = 1;
	parse_file(head, argv[i++], 1);
	while (i <= 3)
	{
		if (argv[i][0] == '\0')
			improved_error(head, " : permission denied", NULL);
		else if (ft_isspace(argv[i][0]) && argv[i][1] == '\0')
			improved_error(head, " : command not found", argv[i]);
		temp->commands = ft_split(argv[i], ' ');
		if (temp->commands == NULL)
			improved_error(head, "malloc failed: Cannot allocate memory", NULL);
		temp->path = get_path(head, temp->commands[0]);
		if (i == 2)
			temp = temp->next;
		i++;
	}
	temp->file = ft_strdup(argv[i]);
}

char	*get_path(t_pipex **head, char *command)
{
	char	**paths;
	char	*command_path;
	int		i;

	paths = ft_split("/bin/ /usr/bin/ /usr/local/bin/", ' ');
	if (paths == NULL)
		improved_error(head, "malloc failed: Cannot allocate memory", NULL);
	i = 0;
	while (i < 3)
	{
		command_path = ft_strjoin(paths[i++], command);
		if (command_path == NULL || (access(command_path, X_OK) == -1 && i == 3)
			|| (access(command_path, X_OK) == 0))
			free_d_array(paths);
		if (access(command_path, X_OK) == -1 && command_path != NULL)
			free(command_path);
		else
			break ;
	}
	if (i == 3)
		improved_error(head, "zsh: command not found: ", command);
	return (command_path);
}
