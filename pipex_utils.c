/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:52 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/28 17:59:25 by ggoncalv         ###   ########.fr       */
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
	t_pipex	*temp;
	int		ret;

	temp = *head;
	if (file_id == 1)
		ret = open(file, O_RDONLY);
	else
	{
		temp = temp->next;
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (ret == -1)
	{
		if (errno == ENOENT)
			improved_error(head, "zsh: no such file or directory: ", file);
		else if (errno == EACCES)
			improved_error(head, "zsh: permission denied: ", file);
		else
			perror("pipex");
	}
	temp->file = ft_strdup(file);
	temp->fd = ret;
}

void	parse_cmd(t_pipex **head, char *argv, int i)
{
	t_pipex	*temp;

	if (i == 2)
		temp = (*head)->next;
	else
		temp = *head;
	if (argv[0] == '\0')
		improved_error(head, " : permission denied", NULL);
	else if (ft_isspace(argv[0] == 1 && argv[1] == '\0'))
		improved_error(head, " : command not found", argv);
	temp->commands = ft_split(argv, ' ');
	if (temp->commands == NULL)
		improved_error(head, "malloc failed: Cannot allocate memory", NULL);
	temp->path = get_path(head, temp->commands[0]);
}

void	parsing_args(int argc, char **argv, t_pipex **head)
{
	t_pipex	*temp;
	int		i;

	if (argc != 5)
		improved_error(NULL, "invalid number of arguments", NULL);
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
	parse_file(head, argv[i], 2);
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

//pegar a envp
