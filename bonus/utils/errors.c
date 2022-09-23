/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 01:47:55 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/03/08 09:15:19 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	ft_putcmderr(char *cmd)
{
	int	i;

	write (2, "zsh: command not found: ", 25);
	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			write(2, &cmd[i], 1);
			i++;
		}
	}
	write (2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	open_pipes(t_data *pipex)
{
	int	i;
	int	size;
	int	*pipes;

	size = (pipex->ac - 4) * 2;
	pipex->pipes = (int *) malloc (size * sizeof(int));
	i = 0;
	while (i < size)
	{
		pipes = pipex->pipes;
		pipe(pipes + i);
		i += 2;
	}
}

void	close_pipes(t_data *pipex)
{
	int	i;
	int	size;
	int	in;
	int	out;

	in = pipex->k_open[0];
	out = pipex->k_open[1];
	size = (pipex->ac - 4) * 2;
	i = 0;
	while (i < size)
	{
		if (i != in && i != out)
			close(pipex->pipes[i]);
		i++;
	}
}

void	close_all_pipes(t_data *pipex)
{
	int	i;
	int	size;

	size = (pipex->ac - 4) * 2;
	i = 0;
	while (i < size)
	{
		close(pipex->pipes[i]);
		i++;
	}
}

void	open_outfile(t_data *pipex)
{
	int	fd;

	if (pipex->here_doc)
	{
		fd = open(pipex->outfile, O_WRONLY | O_CREAT \
				| O_APPEND, 0644);
	}
	else
	{
		fd = open(pipex->outfile, O_WRONLY | O_CREAT \
				| O_TRUNC, 0644);
	}
	if (fd < 0)
	{
		perror(pipex->outfile);
		exit(EXIT_FAILURE);
	}
	pipex->in_out[1] = fd;
}
