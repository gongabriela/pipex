/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:36 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/24 15:05:45 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_child(t_pipex **head, int *fd)
{
	int	file_fd;

	file_fd = open((*head)->file, O_RDONLY);
	if (file_fd == -1)
		error(head);
	dup2(file_fd, STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (execve((*head)->path, (*head)->commands, NULL) == -1)
		error(head);
}

void	exec_parent(t_pipex **head, int *fd)
{
	int		file_fd;
	t_pipex	*parent;

	parent = (*head)->next;
	file_fd = open(parent->file, O_WRONLY);
	if (file_fd == -1)
		error(head);
	dup2(file_fd, STDOUT_FILENO);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (execve(parent->path, parent->commands, NULL) == -1)
		error(head);
}

void	error(t_pipex **head)
{
	free_lst(head);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_pipex	*head;
	pid_t	pid;
	int		fd[2]; //eu tenho que dar free nesse fd tb?

	head = NULL;
	if (argc != 5)
		exit(1);
	init_list(&head);
	if (parsing_args(argv, head) == -1) //fazer esse error handling la tambem para diminuir as linhas???
		error(&head);
	if (pipe(fd) == -1)
		error(&head);
	pid = fork();
	if (pid == -1)
		error(&head);
	if (pid == 0)
		exec_child(&head, fd);
	waitpid(pid, NULL, 0);
	exec_parent(&head, fd);
	free_lst(&head);
	return (0);
}
