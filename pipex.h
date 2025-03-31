/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:25:04 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/31 16:18:48 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./Libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex
{
	char			**commands;
	char			*path;
	char			*file;
	int				fd;
	struct s_pipex	*next;
}					t_pipex;

void	init_list(t_pipex	**head, int argc);
void	free_lst(t_pipex **head);
char	*get_path(t_pipex **head, char *command, char **envp);
void	free_d_array(char **d_array);
void	exec_child(t_pipex **head, char **argv, char **envp, int *fd);
void	exec_child_2(t_pipex **head, char **argv, char **envp, int *fd);
void	exec_process(t_pipex **head, int *fd, int child_num);
void	ft_error(t_pipex **head, char *strerror, char *args);
void	parse_file(t_pipex **head, char *file, int file_id);
char	*ft_print_isspace(char c);
void	parse_cmd(t_pipex **head, char *argv, int i, char **envp);
char	**ft_get_envp(char **envp, t_pipex **head);

//tests:
void	test_list(t_pipex *head);
void	test_init_list(t_pipex *head);

#endif
