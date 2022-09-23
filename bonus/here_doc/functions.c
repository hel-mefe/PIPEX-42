/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 01:38:07 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/02/13 21:33:20 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	ft_putstr(int fd, char *s)
{
	int	i;

	if (fd < 0 || !s)
		return ;
	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	if (fd != 1 && fd != 2)
		close(fd);
}

t_stack	*find_last(t_stack *head)
{
	t_stack	*node;

	node = head;
	while (node->next)
		node = node->next;
	return (node);
}

void	push_tstack(t_stack **head, char *line)
{
	t_stack	*node;
	t_stack	*last;

	node = (t_stack *) malloc (sizeof(t_stack));
	if (!node)
		exit(EXIT_FAILURE);
	node->next = NULL;
	node->line = line;
	if (!(*head))
		*head = node;
	else
	{
		last = find_last(*head);
		last->next = node;
	}
}

int	ft_strcmp_tolimiter(const char *line, const char *limiter)
{
	size_t	i;

	i = 0;
	while ((line[i] || limiter[i]))
	{
		if (line[i] == '\n' && !limiter[i])
			return (0);
		if (line[i] != limiter[i])
			return (line[i] - limiter[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s)
{
	size_t	len;
	size_t	i;
	char	*res;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	res = (char *) malloc ((len + 1) * sizeof(char));
	if (!res)
		exit(EXIT_FAILURE);
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
