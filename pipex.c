/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:24:36 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/03/18 17:36:15 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	if(parsing_args(argc, argv) == 0)
		exit(0);

}

int	parsing_args(int argc, char **argv)
{
	int	fd;

	if (argc != 5)
		exit(0); //not sure if it needs to handle as error if the args are not 4
	if (access(argv[1], R_OK) == -1)
		return(ft_printf("%s\n", strerror(errno)), -1);
	else if (access(argv[4], R_OK) == -1)
		return(ft_printf("%s\n", strerror(errno)), -1);
	if(check_paths(argv) == -1)
		return (-1);
	return (0);
}

int	check_paths(char **argv)
{

}
//parte I - parsing
	//checkar se os arquivos existem e possuem as corretas permissoes
	//checkar se os comandos existem
//parte II - o pipex
	//
