/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:07:53 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/02/13 22:14:27 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_args(char *cmd_path)
{
	size_t	len;
	size_t	j;
	char	**args;

	len = ft_strlen(cmd_path);
	j = len - 1;
	while (j >= 0)
	{
		if (cmd_path[j] == '/')
			break ;
		j--;
	}
	j += 1;
	args = ft_split(cmd_path + j, '/');
	return (args);
}

void	ft_handle_command_path(t_data *pipex, t_queue *node, char **env)
{
	char	**args;
	char	*cmd_path;

	cmd_path = node->args[0];
	args = get_args(cmd_path);
	redirect_output(pipex);
	if (execve(cmd_path, args, env) == -1)
	{
		ft_free_split(args);
		perror(cmd_path);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
}
