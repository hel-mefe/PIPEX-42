/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:03:56 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/03/07 13:08:46 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <fcntl.h>

typedef struct t_list
{
	int		*pipes;
	int		ac;
	int		here_doc;
	int		k_open[2];
	int		in_out[2];
	char	**paths;
}				t_data;

typedef struct t_lists
{
	char			**args;
	struct t_lists	*next;
}				t_queue;

void	run_commands(t_data *pipex, t_queue **node, char **env);
void	increment_counters(t_queue **node, t_data *pipex);
void	redirect_run_command(t_data *pipex, t_queue *node, char **env);
void	redirect_output(t_data *pipex);
char	**ft_get_paths(char **env);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
t_queue	*init_pipex_commands(char **av, int ac, t_data *pipex, char **env);
void	init_pipex_data(char **argv, int ac, t_data *pipex);
t_queue	*find_last_tqueue(t_queue *head);
void	push_tqueue_data(t_queue **head, char *cmd);
char	**ft_split(char const *s, char c);
void	ft_free_t_data(t_data *pipex);
void	ft_free_t_queue(t_queue **head);
void	ft_free_split(char **split);
void	ft_putcmderr(char *cmd);
void	close_all_pipes(t_data *pipex);
void	open_pipes(t_data *pipex);
void	close_pipes(t_data *pipex);
void	ft_handle_command_path(t_data *pipex, t_queue *node, char **env);
char	**get_args(char *cmd_path);

#endif
