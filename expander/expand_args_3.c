/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:40:10 by zmata             #+#    #+#             */
/*   Updated: 2025/09/18 10:36:12 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	ea_is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ea_count_words(const char *s)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ea_is_ifs(s[i]))
			i++;
		if (s[i])
			c++;
		while (s[i] && !ea_is_ifs(s[i]))
			i++;
	}
	return (c);
}

char	*ea_dup_range(const char *s, int a, int b)
{
	char	*res;
	int		k;

	if (b <= a)
		return (ft_strdup(""));
	res = (char *)malloc((b - a + 1) * sizeof(char));
	if (!res)
		return (NULL);
	k = 0;
	while (a < b)
		res[k++] = s[a++];
	res[k] = '\0';
	return (res);
}

/* même logique, mais 4 arguments max */
static int	ea_append_word(const char *p, int len, char **tab, int *idx)
{
	char	*w;
	int		k;

	w = (char *)malloc((len + 1) * sizeof(char));
	if (!w)
	{
		while (*idx > 0)
		{
			(*idx)--;
			free(tab[*idx]);
		}
		return (1);
	}
	k = 0;
	while (k < len)
	{
		w[k] = p[k];
		k++;
	}
	w[len] = '\0';
	tab[*idx] = w;
	(*idx)++;
	return (0);
}

int	ea_fill_words(const char *s, char **tab)
{
	int	i;
	int	idx;
	int	start;

	i = 0;
	idx = 0;
	while (s[i])
	{
		while (s[i] && ea_is_ifs(s[i]))
			i++;
		start = i;
		while (s[i] && !ea_is_ifs(s[i]))
			i++;
		if (i > start)
			if (ea_append_word(s + start, i - start, tab, &idx))
				return (1);
	}
	tab[idx] = NULL;
	return (0);
}
