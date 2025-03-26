/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:36 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/26 19:59:47 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_child(t_pipex **head, int *fd)
{
	int	file_fd;

	file_fd = open((*head)->file, O_RDONLY);
	if (file_fd == -1)
		improved_error(head, "could not open file", NULL);
	dup2(file_fd, STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve((*head)->path, (*head)->commands, NULL) == -1)
		improved_error(head, "execve() failed", NULL);
}

void	exec_child_2(t_pipex **head, int *fd)
{
	int		file_fd;
	t_pipex	*parent;

	parent = (*head)->next;
	file_fd = open(parent->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
		parse_file_1(head, parent->file);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
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

	head = NULL;
	if (argc != 5)
		exit(1);
	init_list(&head);
	parsing_args(argv, &head);
	if (pipe(fd) == -1)
		improved_error(&head, "pipe() failed", NULL);
	exec_process(&head, fd, 1);
	close(fd[1]);
	exec_process(&head, fd, 2);
	close(fd[0]);
	free_lst(&head);
	return (0);
}
//parsing de "" e whitespaces pros comandos
//melhorar mensagens de erro
//diminuir funcao parsing args
//tratar do /dev/urandom - pesquisar waitpid wnohang
// /dev/urandom cat head -5 outfile

//quando o nome do arquivo tem um typo (ou seja, ele nao existe), a mensagem tem que ficar assim:
	//cat Mkefile
		//cat: Mkefile: No such file or directory
			//lembrando de verificar o comando tambem! pq se for por exemplo ct Mkefile tem q printar ct: command not found, e nao ct: Mkefile: command not found

//usando essa sintaxe: <Makefile cat | wc -l > outfile
//se escreversmos mkefile ct, o output e: -bash: Mkefile: No such file or directory

//tem ou nao tem \n no fim das mensagens do shel???? alguns erros tao com e outros tao sem,


//TESTES
	//file1
		//nao existe
		//permissoes r,w,x
	//cmd1
		//nao existe
	//cmd2
		//nao existe
	//file2
		//nao existe
		//permissoes r,w,x
