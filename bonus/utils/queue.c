/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:36:48 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/03/08 09:11:21 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

t_queue	*find_last_tqueue(t_queue *head)
{
	t_queue	*node;

	if (!head)
		return (NULL);
	node = head;
	while (node->next)
		node = node->next;
	return (node);
}

void	push_tqueue_data(t_queue **head, char *cmd)
{
	t_queue	*node;
	t_queue	*last;

	node = (t_queue *) malloc (sizeof(t_queue));
	node->args = ft_split(cmd, ' ');
	node->next = NULL;
	if (!(*head))
		*head = node;
	else
	{
		last = find_last_tqueue(*head);
		last->next = node;
	}
}

t_queue	*init_pipex_commands(char **av, int ac, t_data *pipex, char **env)
{
	t_queue	*head;
	int		i;

	head = NULL;
	if (pipex->here_doc)
		i = 3;
	else if (access(av[1], R_OK))
	{
		i = 3;
		pipex->k_open[0] += 2;
		pipex->k_open[1] += 2;
	}
	else
		i = 2;
	while (i < ac - 1)
	{
		push_tqueue_data(&head, av[i]);
		i++;
	}
	pipex->paths = ft_get_paths(env);
	return (head);
}

void	init_pipex_data(char **argv, int ac, t_data *pipex)
{
	pipex->k_open[0] = -2;
	pipex->k_open[1] = 1;
	pipex->outfile = argv[ac - 1];
	pipex->ac = ac;
	if (!ft_strcmp(argv[1], "here_doc"))
		pipex->here_doc = 1;
	else
	{
		pipex->here_doc = 0;
		if (!access(argv[1], R_OK))
			pipex->in_out[0] = open(argv[1], O_RDONLY);
		else
			perror(argv[1]);
	}
	if (pipex->in_out[1] < 0)
		perror(argv[ac - 1]);
	open_pipes(pipex);
}
