/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:36 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/20 16:52:25 by ggoncalv         ###   ########.fr       */
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
		//node->commands = NULL;
		node->path = NULL;
		node->file = NULL;
		node->next = NULL;
	}
}

void	free_lst(t_pipex **head)
{
	t_pipex	*temp;
	t_pipex	*next;
	int		i;

	temp = *head;
	while (temp != NULL)
	{
		next = temp->next;
		if (temp->commands != NULL)
		{
			i = 0;
			while (temp->commands[i] != NULL)
				free(temp->commands[i++]);
			free(temp->commands);
		}
		if (temp->path != NULL)
			free(temp->path);
		if (temp->file != NULL)
			free(temp->file);
		free(temp);
		temp = next;
	}
	*head = NULL;
}

int	parsing_args(char **argv, t_pipex *head)
{
	int		i;

	i = 1;
	while (i <= 3)
	{
		if (access(argv[i], R_OK) == -1)
			return(ft_printf("Error: %s\n", strerror(errno)), -1);
		else
			head->file = argv[i];
		i++;
		head->commands = ft_split(argv[i], ' ');
		if (head->commands == NULL)
			return (-1);
		head->path = get_path(head->commands[0]);
		if (head->path == NULL)
			return (-1);
		i++;
		head = head->next;
	}
	return (0);
}

char	*get_path(char *command)
{
	char	**paths;
	char	*command_path;
	int		i;
	int		j;

	paths = ft_split("/bin/ /usr/bin/ /usr/local/bin/", ' ');
	if (paths == NULL)
		return (NULL);
	i = 0;
	j = 0;

	while (i < 3)
	{
		command_path = ft_strjoin(paths[i++], command);
		if (command_path == NULL || (access(command_path, X_OK) == -1 && i == 3) || (access(command_path, X_OK) == 0))
		{
			while (paths[j])
				free(paths[j++]);
			free(paths);
		}
		if (access(command_path, X_OK) == -1)
			free(command_path);
		else
			break ;
	}
	if (i == 3)
		return (ft_printf("Error: %s\n", strerror(errno)), NULL);
	return (command_path);
}

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
	return(0);
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
