/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 21:45:55 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/03/07 12:58:11 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_queue	*init_pipex_commands(char **av, int ac, t_data *pipex, char **env)
{
	t_queue	*head;
	int		i;

	head = NULL;
	if (access(av[1], R_OK))
		i = 3;
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
	pipex->ac = ac;
	pipex->here_doc = 0;
	if (!access(argv[1], R_OK))
		pipex->in_out[0] = open(argv[1], O_RDONLY);
	else
	{
		perror(argv[1]);
		pipex->k_open[0] += 2;
		pipex->k_open[1] += 2;
	}
	pipex->in_out[1] = open(argv[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->in_out[1] < 0)
		perror(argv[ac - 1]);
	open_pipes(pipex);
}

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
