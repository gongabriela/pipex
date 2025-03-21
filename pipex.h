/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:25:04 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/21 16:40:04 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./Libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipex
{
	char			**commands;
	char			*path;
	char			*file;
	struct s_pipex	*next;
}					t_pipex;

void	init_list(t_pipex	**head);
void	free_lst(t_pipex **head);
int		parsing_args(char **argv, t_pipex *head);
char	*get_path(char *command);
void	free_d_array(char **d_array);

//tests:
void	test_list(t_pipex *head);
void	test_init_list(t_pipex *head);

#endif
