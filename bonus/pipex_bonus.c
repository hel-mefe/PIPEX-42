/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 01:29:51 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/03/14 12:12:46 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	redirect_output(t_data *pipex)
{
	int	pipe_size;
	int	in;
	int	out;

	in = pipex->k_open[0];
	out = pipex->k_open[1];
	pipe_size = (pipex->ac - 4) * 2;
	if (pipex->k_open[0] < 0)
	{
		dup2(pipex->in_out[0], 0);
		dup2(pipex->pipes[out], 1);
	}
	else if (pipex->k_open[1] >= pipe_size)
	{
		open_outfile(pipex);
		dup2(pipex->in_out[1], 1);
		dup2(pipex->pipes[in], 0);
	}
	else
	{
		dup2(pipex->pipes[out], 1);
		dup2(pipex->pipes[in], 0);
	}
}

void	redirect_run_command(t_data *pipex, t_queue *node, char **env)
{
	int		i;
	char	*cmd_path;

	if (!node->args[0])
		ft_putcmderr(node->args[0]);
	if (node->args[0][0] == '/')
		ft_handle_command_path(pipex, node, env);
	close_pipes(pipex);
	i = 0;
	while (pipex->paths[i])
	{
		cmd_path = ft_strjoin(pipex->paths[i], node->args[0]);
		if (!access(cmd_path, X_OK))
		{
			redirect_output(pipex);
			execve(cmd_path, node->args, env);
			exit(EXIT_FAILURE);
		}
		if (cmd_path)
			free(cmd_path);
		i++;
	}
	ft_putcmderr(node->args[0]);
	exit(EXIT_FAILURE);
}

void	increment_counters(t_queue **node, t_data *pipex)
{
	*node = (*node)->next;
	pipex->k_open[0] += 2;
	pipex->k_open[1] += 2;
}

void	run_commands(t_data *pipex, t_queue **node, char **env)
{
	while (*node)
	{
		if (fork() == 0)
		{
			redirect_run_command(pipex, *node, env);
			close_all_pipes(pipex);
			exit(EXIT_FAILURE);
		}
		increment_counters(node, pipex);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data		pipex;
	t_queue		*head;
	t_queue		*node;

	if (ac < 5)
		exit(EXIT_FAILURE);
	init_pipex_data(av, ac, &pipex);
	head = init_pipex_commands(av, ac, &pipex, env);
	if ((ac < 5 && !pipex.here_doc) || (pipex.here_doc && ac != 6))
		return (EXIT_FAILURE);
	node = head;
	if (pipex.here_doc)
		handle_here_doc(&pipex, av[2]);
	run_commands(&pipex, &node, env);
	close_all_pipes(&pipex);
	while (1)
		if (wait(NULL) == -1)
			break ;
	return (0);
}
