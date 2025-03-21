#include "pipex.h"

void	test_list(t_pipex *head)
{
	int	i;

	i = 1;
	while (head != NULL)
	{
		ft_printf("node %d allocated!\n", i++);
		if (head->commands == NULL && head->path == NULL && head->file == NULL)
			ft_printf("all variables are set to NULL in this node!\n");
		else
			ft_printf("error setting variables to NULL in this node!\n");
		head = head->next;
	}
}

void	test_init_list(t_pipex *head)
{
	int	i;

	while (head != NULL)
	{
		if (head->commands != NULL)
		{
			ft_printf("commands variable:\n");
			i = 0;
			while(head->commands[i])
				ft_printf("%s\n", head->commands[i++]);
		}
		if (head->path != NULL)
			ft_printf("path: %s\n", head->path);
		if (head->file != NULL)
			ft_printf("file: %s\n", head->file);
		head = head->next;
	}
}
