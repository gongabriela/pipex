/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:52 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/31 16:33:33 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_list(t_pipex	**head, int argc)
{
	t_pipex	*node;
	int		i;

	if (argc != 5)
		ft_error(NULL, "invalid number of arguments", NULL);
	i = 0;
	*head = NULL;
	while (i++ < 2)
	{
		node = (t_pipex *)malloc(sizeof(t_pipex));
		if (node == NULL)
			ft_error(head, "malloc failed: Cannot allocate memory", NULL);
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
	int		file_fd;

	temp = *head;
	if (file_id == 1)
		file_fd = open(file, O_RDONLY);
	else
	{
		temp = temp->next;
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (file_fd == -1)
	{
		if (errno == ENOENT)
			ft_error(head, "zsh: no such file or directory: ", file);
		else if (errno == EACCES)
			ft_error(head, "zsh: permission denied: ", file);
		else
			perror("pipex");
	}
	temp->file = ft_strdup(file);
	temp->fd = file_fd;
}

void	parse_cmd(t_pipex **head, char *argv, int i, char **envp)
{
	t_pipex	*temp;

	if (i == 2)
		temp = (*head)->next;
	else
		temp = *head;
	if (argv[0] == '\0')
		ft_error(head, " : permission denied", NULL);
	else if (ft_isspace(argv[0] == 1 && argv[1] == '\0'))
		ft_error(head, " : command not found", argv);
	temp->commands = ft_split(argv, ' ');
	if (temp->commands == NULL)
		ft_error(head, "malloc failed: Cannot allocate memory", NULL);
	temp->path = get_path(head, temp->commands[0], envp);
}

char	*get_path(t_pipex **head, char *command, char **envp)
{
	char	*path;
	char	*path_bar;
	char	**split_paths;
	int		i;

	split_paths = ft_get_envp(envp, head);
	i = 0;
	while (split_paths[i] != NULL)
	{
		path_bar = ft_strjoin(split_paths[i], "/");
		if (path_bar == NULL)
			return (free_d_array(split_paths), ft_error(head, "malloc failed", NULL), NULL);
		path = ft_strjoin(path_bar, command);
		if (path == NULL)
			return (free_d_array(split_paths), ft_error(head, "malloc failed", NULL), NULL);
		free(path_bar);
		if (access(path, X_OK) == 0)
			return (free_d_array(split_paths), path);
		free(path);
		i++;
	}
	return (free_d_array(split_paths), ft_error(head, "command not found : ", command), NULL);
}

char	**ft_get_envp(char **envp, t_pipex **head)
{
	char	**paths;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			break ;
		envp++;
	}
	if (*envp == NULL)
		ft_error(head, "PATH not found in env", NULL);
	paths = ft_split(*envp + 5, ':');
	if (paths == NULL)
		ft_error(head, "malloc failed: Cannot allocate memory", NULL);
	return (paths);
}
