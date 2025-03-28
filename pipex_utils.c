/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:52 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/28 20:32:20 by ggoncalv         ###   ########.fr       */
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

void	parse_cmd(t_pipex **head, char *argv, int i,char **envp)
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
	temp->path = get_path(head, temp->commands[0], envp);
}

/*void	parsing_args(int argc, char **argv, t_pipex **head)
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
}*/

//extrair a linha path= do envp sem incluir o PATH=
char	*get_path(t_pipex **head, char *command, char **envp)
{
	char	*paths;
	char	*command_path;

	paths = ft_get_envp(envp);
	if (paths == NULL)
		improved_error(head, "path not found on envp", NULL);
	command_path = ft_strjoin(paths, command);
	if (command_path == NULL || access(command_path, X_OK) == -1)
	{
		free(command_path);
		improved_error(head, "zsh: command not found: ", command);
	}
	return (command_path);
}

//pegar a envp

char *ft_get_envp(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (*envp)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		envp++;
	}
	if (envp[i] != NULL)
	{
		path = ft_strdup(*envp + 5);
		return (path);
	}
	return (NULL);
}

//ver github do mano e dividir o PATH=
/*char *ft_get_envp(char **envp) {
    while (*envp) {
        if (strncmp(*envp, "PATH=", 5) == 0)
            return *envp + 5;  // Skip "PATH="
        envp++;
    }
    return NULL;
}*/
