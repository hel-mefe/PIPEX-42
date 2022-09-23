/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 01:45:49 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/03/08 09:19:44 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	join_all_lines(t_stack **head, t_data *pipex, char **line)
{
	int	fd;
	int	out;

	out = pipex->k_open[1];
	fd = pipex->pipes[1];
	*line = ft_join_lines(*head);
	ft_free_lines_list(head);
	ft_putstr(fd, *line);
	if (*line)
		free (*line);
	*line = NULL;
	pipex->k_open[0] += 2;
	pipex->k_open[1] += 2;
}

char	*join_lines(char *line1, char *line2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*res;

	if (!line1)
		return (ft_strdup(line2));
	len = ft_strlen(line1) + ft_strlen(line2);
	res = (char *) malloc ((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len && line1[i])
		res[i] = line1[i];
	j = 0;
	while (i < len && line2[j])
		res[i++] = line2[j++];
	res[i] = 0;
	free (line1);
	return (res);
}

char	*ft_join_lines(t_stack *head)
{
	t_stack	*node;
	char	*line;

	line = NULL;
	node = head;
	while (node)
	{
		line = join_lines(line, node->line);
		if (!line)
			exit(EXIT_FAILURE);
		node = node->next;
	}
	return (line);
}

void	add_character(char **s, char c)
{
	size_t	len;
	size_t	i;
	char	*line;
	char	*res;

	len = ft_strlen(*s);
	res = (char *) malloc ((len + 2) * sizeof(char));
	if (!res)
		exit(EXIT_FAILURE);
	i = 0;
	line = *s;
	while (i < len && *s)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = c;
	i += 1;
	res[i] = 0;
	free(line);
	*s = res;
}

void	handle_here_doc(t_data *pipex, char *limiter)
{
	t_stack	*head;
	char	c;
	char	*line;

	head = NULL;
	c = 0;
	line = NULL;
	ft_putstr(1, "pipe heredoc> ");
	while (read(0, &c, 1) == 1)
	{
		add_character(&line, c);
		if (c == 0 || (c == '\n' && ft_strcmp_tolimiter(line, limiter)))
		{
			push_tstack(&head, ft_strdup(line));
			ft_free_line(&line);
			ft_putstr(1, "pipe heredoc> ");
		}
		else if (c == '\n' && !ft_strcmp_tolimiter(line, limiter))
			break ;
	}
	ft_free_line(&line);
	join_all_lines(&head, pipex, &line);
}
