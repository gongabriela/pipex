/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:36 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/28 11:49:31 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_child(t_pipex **head, int *fd)
{
	dup2((*head)->fd, STDIN_FILENO);
	close((*head)->fd);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve((*head)->path, (*head)->commands, NULL) == -1)
		improved_error(head, "execve() failed", NULL);
}

void	exec_child_2(t_pipex **head, int *fd)
{
	t_pipex	*parent;

	parent = (*head)->next;
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(parent->fd, STDOUT_FILENO);
	close(parent->fd);
	close(fd[1]);
	if (execve(parent->path, parent->commands, NULL) == -1)
		improved_error(head, "execve() failed", NULL);
}

void	exec_process(t_pipex **head, int *fd, int child_num)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		improved_error(head, "fork() failed", NULL);
	if (pid == 0)
	{
		if (child_num == 1)
			exec_child(head, fd);
		else
			exec_child_2(head, fd);
	}
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv)
{
	t_pipex	*head;
	int		fd[2];
	pid_t	pid_1;
	pid_t	pid_2;

	head = NULL;
	init_list(&head);
	parsing_args(argc, argv, &head);
	if (pipe(fd) == -1)
		improved_error(&head, "pipe() failed", NULL);
	pid_1 = fork();
	if (pid_1 == -1)
		improved_error(&head, "fork() failed", NULL);
	if (pid_1 == 0)
		exec_child(&head, fd);
	pid_2 = fork();
	if (pid_2 == -1)
		improved_error(&head, "fork() failed", NULL);
	if (pid_2 == 0)
		exec_child_2(&head, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
	free_lst(&head);
	return (0);
}
//tratar do /dev/urandom - pesquisar waitpid wnohang
// /dev/urandom cat head -5 outfile

//criar uma nova branch para testar o seguinte

//child process 1:
	//parse file
	//parse cmd
	//execve
//child process 2:
	//parse file
	//parse cmd
	//execve
//parent process
	//init_list
	//fork()
		//child_1
	//fork()
		//child_2
	//waitpid
	//waitpid
	//free_lst

//descobrir o que e o envp
