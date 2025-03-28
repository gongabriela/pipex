/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:36 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/28 17:59:40 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_child(t_pipex **head, char **argv, int *fd)
{
	parse_file(head, argv[1], 1);
	parse_cmd(head, argv[2], 1);
	dup2((*head)->fd, STDIN_FILENO);
	close((*head)->fd);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve((*head)->path, (*head)->commands, NULL) == -1)
		improved_error(head, strerror(errno), NULL);
}

void	exec_child_2(t_pipex **head, char **argv, int *fd)
{
	t_pipex	*parent;

	parse_file(head, argv[4], 2);
	parse_cmd(head, argv[3], 2);
	parent = (*head)->next;
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(parent->fd, STDOUT_FILENO);
	close(parent->fd);
	close(fd[1]);
	if (execve(parent->path, parent->commands, NULL) == -1)
		improved_error(head, strerror(errno), NULL);
}

int	main(int argc, char **argv)
{
	t_pipex	*head;
	int		fd[2];
	pid_t	pid_1;
	pid_t	pid_2;

	if (argc != 5)
		improved_error(NULL, "invalid number of arguments", NULL);
	head = NULL;
	init_list(&head);
	if (pipe(fd) == -1)
		improved_error(&head, "pipe() failed", NULL);
	pid_1 = fork();
	if (pid_1 == -1)
		improved_error(&head, "fork() failed", NULL);
	if (pid_1 == 0)
		exec_child(&head, argv, fd);
	pid_2 = fork();
	if (pid_2 == -1)
		improved_error(&head, "fork() failed", NULL);
	if (pid_2 == 0)
		exec_child_2(&head, argv, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
	free_lst(&head);
	return (0);
}

//implementar um
