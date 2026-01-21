/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:09:59 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 19:12:50 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_stat(const char *path)
{
	struct stat	st;

	return (stat(path, &st));
}

int	ft_is_dir(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

int	ft_is_file(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISREG(st.st_mode));
}

int	ft_not_dir_but_file(char *path)
{
	int	is_file;
	int	n;

	is_file = 0;
	if (ft_strcmp(path, "/") == 0)
		return (0);
	if (path && *path && (path[ft_strlen(path) - 1] == '/'))
	{
		n = ft_strlen(path) - 1;
		path[n] = 0;
		if (ft_is_file(path))
			is_file = 1;
		path[n] = '/';
	}
	return (is_file);
}
