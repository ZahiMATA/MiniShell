/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:52:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/03 17:17:27 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_split_first(const char *s, char **key, char **val, char c)
{
	char *i;

	i = ft_strchr(s, c);
	if (i == NULL)
	{
		*key = strdup(s);
		if (*key == NULL)
			return NULL;
		*val = NULL;
		return (*key);
	}
	*key = ft_strndup(s, i -s);
	if (*key == NULL)
		return (NULL);
	*val = ft_strdup(i + 1);
	if (*val == NULL)
	{
		mem_free(*key, "ft_split_first", *key);
		return (NULL);
	}
	return (*key);
}
