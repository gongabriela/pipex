/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:36 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/13 14:56:10 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int		fd[2];
	int		txt_fd;
	pid_t	pid;
	char	*path;
	char	*path_cmd;

	(void)argc;
	path = "/bin/";
	if (pipe(fd) == -1)
		return 1;
	pid = fork();
	if (pid < 0)
		return 1;
	if (pid == 0)
	{
		close (fd[0]);
		txt_fd = open(argv[2], O_RDONLY);
		if (txt_fd == -1)
			return 1;
		dup2(txt_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(txt_fd);
		close(fd[1]);
		path_cmd = ft_strjoin(path, argv[1]);
		execve(path_cmd, &argv[1], NULL);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		path_cmd = ft_strjoin(path, argv[3]);
		execve(path_cmd, &argv[3], NULL);
	}
	return (0);
}

