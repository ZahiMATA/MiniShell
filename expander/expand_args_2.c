/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:10:05 by zmata             #+#    #+#             */
/*   Updated: 2025/09/19 10:54:15 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		ea_count_words(const char *s);
int		ea_fill_words(const char *s, char **tab);
char	*ea_dup_range(const char *s, int a, int b);
int		ea_is_ifs(char c);

int	ea_has_dollar(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		if (s[i++] == '$')
			return (1);
	return (0);
}

int	ea_has_any_quote(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		if (s[i] == '\'' || s[i++] == '\"')
			return (1);
	return (0);
}

void	ea_free_container_only(char **t)
{
	if (t)
		free(t);
}

char	**ea_split_ifs_words(const char *s)
{
	char	**tab;
	int		count;

	if (!s)
		return (NULL);
	count = ea_count_words(s);
	if (count <= 1)
		return (NULL);
	tab = (char **)malloc((count + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	if (ea_fill_words(s, tab))
		return (free(tab), NULL);
	return (tab);
}
