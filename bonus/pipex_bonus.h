/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:15:00 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/03/08 09:15:31 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	char	*outfile;
}	t_data;

typedef struct t_lists
{
	char			**args;
	struct t_lists	*next;
}	t_queue;

typedef struct t_link
{
	char			*line;
	struct t_link	*next;
}	t_stack;

void	run_commands(t_data *pipex, t_queue **node, char **env);
void	increment_counters(t_queue **node, t_data *pipex);
void	init_pipex_data(char **argv, int ac, t_data *pipex);
t_queue	*init_pipex_commands(char **av, int ac, t_data *pipex, char **env);
void	redirect_run_command(t_data *pipex, t_queue *node, char **env);
void	redirect_output(t_data *pipex);
void	push_tqueue_data(t_queue **head, char *cmd);
t_queue	*find_last_tqueue(t_queue *head);
char	**ft_split(const char *s, char c);
char	**ft_get_paths(char **env);
char	*ft_join_paths(const char *s1, const char *s2);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	push_data(t_queue **head, char *cmd);
void	ft_free_split(char **split);
void	ft_free_t_queue(t_queue **head);
void	ft_free_t_data(t_data *pipex);
void	close_pipes(t_data *pipex);
void	open_pipes(t_data *pipex);
void	close_all_pipes(t_data *pipex);
void	ft_putcmderr(char *cmd);
void	open_outfile(t_data *pipex);
void	handle_here_doc(t_data *pipex, char *limiter);
void	ft_putstr(int fd, char *s);
void	push_tstack(t_stack **head, char *line);
int		ft_strcmp_tolimiter(const char *line, const char *limiter);
void	add_character(char **s, char c);
char	*join_lines(char *line1, char *line2);
char	*ft_join_lines(t_stack *head);
void	join_all_lines(t_stack **head, t_data *pipex, char **line);
void	ft_free_lines_list(t_stack **head);
char	*ft_strdup(char *s);
void	ft_free_line(char **line);
void	ft_handle_command_path(t_data *pipex, t_queue *node, char **env);
char	**get_args(char *cmd_path);

#endif
