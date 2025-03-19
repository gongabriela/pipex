/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:36 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/19 14:09:18 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

ft_free_nodes(t_pipex **head)
{
	//dar free em tudo
	//precisa dar free individualmente em cada var?
	//por ex a var **commands, preciso dar free separadamente
		//pq e um **?
}
void	init_list(t_pipex	**head)
{
	t_pipex	*node;

	node = (t_pipex *)malloc(sizeof(t_pipex));
	if (node == NULL)
		exit(0); //ver se consegue dar exit com mensagem de erro de malloc!
	*head = node;
	node = (t_pipex *)malloc(sizeof(t_pipex));
	if (node == NULL)
	{
		//dar free no node anterior
		//retornar erro de malloc
	}
	(*head)->next = node;
	node->next = NULL;
}

int	parsing_args(int argc, char **argv, t_pipex *head)
{
	int		i;

	i = 1;
	while (i <= 3)
	{
		if (access(argv[i], R_OK) == -1)
			//dar free em tudo e retornar erro de permission denied
		else
			head->file = argv[i];
		i++;
		head->commands = ft_split(argv[i], ' ');
		head->path = NULL;
		head->path = get_path(head->commands[0]);
		if (head->path == NULL)
			//dar free em tudo e erro de command not found
		i++;
		head = head->next;
	}
	return (0);
}

char	*get_paths(char *command)
{
	char	**paths;
	char	*command_path;
	int		i;
	int		j;

	paths = ft_calloc(4, sizeof(char *));
	if (paths == NULL)
		return (NULL);
	paths[0] = "/bin/";
	paths[1] = "/usr/bin/";
	paths[2] = "/usr/local/bin/";
	i = 0;
	while (i < 3)
	{
		command_path = ft_strjoin(paths[i++], command);
		if (command_path == NULL)
			return (NULL); //e dar free no paths
		if (access(command_path, X_OK) == 0)
			break ;
	}
	j = 0;
	while (j <= 3)
	{
		free(paths[j++]);
	}
	free(paths);
	if (i == 3)
		return (free(command_path), NULL);
	return (command_path);
}

int	main(int argc, char **argv)
{
	int		fd[2];
	pid_t	pid;
	t_pipex	*head;

	if (argc != 5)
		exit(0);
	init_list(&head);
	if (parsing_args(argc, argv, head) == -1)
		return(/*dar free em tudo e exit*/0);
	if (pipe(fd) == -1)
		return(/*dar free em tudo e exit*/0);
	pid = fork();
	if (pid == -1)
		return(/*dar free em tudo e exit*/0);
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
}

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
