/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 01:33:03 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/02/13 19:11:05 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	ft_free_lines_list(t_stack **head)
{
	t_stack	*prev;
	t_stack	*node;

	node = *head;
	prev = node;
	while (prev)
	{
		prev = node;
		if (!prev)
			break ;
		if (node)
			node = node->next;
		free(prev->line);
		prev->line = NULL;
		free(prev);
	}
}

void	ft_free_line(char **line)
{
	if (!(*line) || !line)
		return ;
	free(*line);
	*line = NULL;
}
