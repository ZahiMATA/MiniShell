/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:55:43 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 14:48:07 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS char **ft_split(char const *s, char c);
 * @RETOUR Alloue (avec malloc(3)) et retourne un tableau de chaînes de
 * caractères obtenu en séparant ’s’ à l’aide du caractère ’c’, utilisé comme
 * délimiteur. Le tableau doit être terminé par NULL
 * @IN  ft_split "abxxxcd" "x"
 * @OUT          "ab" "cd"
 */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static char	*alloc_word(char const *s, char c, size_t index, size_t *len)
{
	size_t	i;
	char	*zone;

	*len = 0;
	while (s[*len + index] && s[*len + index] != c)
		(*len)++;
	zone = mem_malloc((*len + 1) * sizeof(char), "alloc_word", s + index);
	if (zone == NULL)
		return (NULL);
	i = 0;
	while (i < *len)
	{
		zone[i] = s[i + index];
		i++;
	}
	zone[*len] = '\0';
	return (zone);
}

static int	compter_mots(char const *s, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			n++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (n);
}

static int	manage_zone(char **split, char *zone, size_t *n)
{
	if (zone == NULL)
	{
		while (*n > 0)
			free(split[--(*n)]);
		free(split);
		return (-1);
	}
	return (0);
}

static int	do_split(char const *s, char c, char **split)
{
	size_t	next;
	size_t	n;
	size_t	i;
	size_t	len;
	char	*zone;

	n = 0;
	i = 0;
	len = compter_mots(s, c);
	while (s[i] && len != 0)
	{
		while (s[i] && s[i] == c)
			i++;
		zone = alloc_word(s, c, i, &next);
		if (manage_zone(split, zone, &n) == -1)
			return (-1);
		split[n++] = zone;
		i += next;
		while (s[i] && s[i] == c)
			i++;
	}
	split[len] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**split;

	len = compter_mots(s, c);
	split = mem_malloc((len + 1) * sizeof(char *), "ft_split", s);
	if (split == NULL)
		return (NULL);
	{
		if (do_split(s, c, split) == -1)
			return (NULL);
	}
	return (split);
}
/*
#include <stdio.h>
#include <stdlib.h>

void test3(char const *s1, char const *s2)
{
        char *sdup1 = ft_strdup(s1);
        char *sdup2 = ft_strdup(s2);
        char **ret  = ft_split(sdup1, sdup2[0]);
        int i = 0;
	printf("str:%p:%s\n", s1, s2);
        printf("str:%p:%s\n", s2, s2);
        printf("str:%p:%s\n", sdup1, sdup1);
        printf("str:%p:%s\n", sdup2, sdup2);
        while(i < 20)
	{
		printf("ret:%p:%s\n", ret[i], ret[i]);
		i++;
	}
        free(sdup1);
        free(sdup2);
        free(ret);
}

void test4(char const *s1, char const *s2, int n)
{
        char *sdup1 = ft_strdup(s1);
        char *sdup2 = ft_strdup(s2);
        char *ret;
        int i = 0;
	int nb = compter_mots(s1, s2[0]);
	size_t next;
	while(i < n)
	{
		ret = allouer_mot(sdup1, sdup2[0], i, &next);
		printf("ret:nb=%d:next%lu:i=%i:%p:%s\n", nb, next, i, ret, ret);
		i++;
		if (*ret) break;
	}
        free(sdup1);
        free(sdup2);
        free(ret);
}

int     main(int argc, char *argv[])
{
        if (argc == 3) test3(argv[1], argv[2]);
	else if (argc == 4) test4(argv[1], argv[2], atoi(argv[3]));
	else printf("Wrong params!");
}
*/
