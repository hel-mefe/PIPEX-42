/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 01:48:41 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/02/13 18:16:42 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	ft_free_t_data(t_data *pipex)
{
	t_data	*node;

	node = pipex;
	ft_free_split(node->paths);
	free(node->pipes);
	node->pipes = NULL;
	pipex = NULL;
}

void	ft_free_t_queue(t_queue **head)
{
	t_queue	*node;
	t_queue	*prev;

	node = *head;
	prev = node;
	while (prev)
	{
		prev = node;
		if (node)
			node = node->next;
		if (!prev)
			break ;
		ft_free_split(prev->args);
		free(prev);
	}
	*head = NULL;
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
}
