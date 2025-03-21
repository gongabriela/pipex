/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:36 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/21 16:43:31 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	t_pipex	*head;

	(void)argv;
	head = NULL;
	if (argc != 5)
		exit(1);
	init_list(&head);
	test_list(head);
	if (parsing_args(argv, head) == -1)
	{
		ft_printf("error in args!\n");
		free_lst(&head);
		exit(1);
	}
	test_init_list(head);
	free_lst(&head);
	return (0);
}

/*int	main(int argc, char **argv)
{
	int		fd[2];
	pid_t	pid;
	t_pipex	*head;

	if (argc != 5)
		exit(0);
	init_list(&head);
	if (parsing_args(argc, argv, head) == -1)
		return(dar free em tudo e exit);
	if (pipe(fd) == -1)
		return(dar free em tudo e exit0);
	pid = fork();
	if (pid == -1)
		return(dar free em tudo e exit0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		//executar comando 1
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		//executar comando 2
		close(fd[0]);
	}
	return (0);
}*/

//parte I - parsing
	//checkar se os arquivos existem e possuem as corretas permissoes
	//checkar se os comandos existem
	//criar dois nos - um para o primeiro comando, outro para o 2 comando
	//guardar o nome do arquivo e o path do comando (?)
	//guardar fds do comando?

/*parte II - o pipex
	//basicamente iremos utilizar da funcao execve() para executar os comandos.
	//mas essa funcao substitui o processo atual pelo do comando. por isso, temos
	que criar um outro processo, um filho, e fazemos isso com o fork().
	o processo filho sera uma copia exata do pai a partir da linha que vc chama o fork,
	e os dois comecam a executar do mesmo ponto imediatamente apos o fork()
	//mas eles terao PID diferentes, e por isso podemos manipular os processos
	dessa forma, no mesmo codigo

	*/

/*
	1. iniciar a lista. criar os dois nodes que representam os dois comandos separados pelo pipe
	2. verificar se os arquivos podem ser acessados. se sim, adicionar nos respectivos nos, se nao, dar free em tudo e retornar erro.
	3. verificar se os comandos podem ser acessados. mesma coisa que os arquivos
*/
