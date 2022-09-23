/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:36:58 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/03/21 19:36:18 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	**ft_get_paths(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (!(env[i]))
	{
		write (2, "PIPEX: PATH WAS NOT FOUND!", 26);
		exit(EXIT_FAILURE);
	}
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		exit(EXIT_FAILURE);
	return (paths);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*res;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *) malloc ((len + 2) * sizeof(char));
	if (!res)
		exit(EXIT_FAILURE);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	res[i++] = '/';
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = 0;
	return (res);
}
