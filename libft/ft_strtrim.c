/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:06:25 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/12 14:42:38 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS char *ft_strtrim(char const *s1, char const *set);
 * @RETOUR Alloue (avec malloc(3)) et retourne une copie de la chaîne ’s1’,
 * sans les caractères spécifiés dans ’set’ au début et à la fin de la chaîne
 * de caractères.
 * @IN ft_strtrim "---a-b-c--" "-" ; "--a-b" "-", "a-b---" "-", "a-b" "-"
 * @OUT           "a-b-c"      "-" ; "a-b"   "-", "a-b"    "-", "a-b" "-"
 */

#include "libft.h"
#include <stdlib.h>

static	int	is_in_set(char const car, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] && set[i] != car)
		i++;
	if (set[i] == car)
		return (1);
	return (0);
}

static void	copier_tab(char *dest, char const *src, size_t i1, size_t i2)
{
	size_t	i;

	i = 0;
	while (i1 + i < i2 + 1 && src[i1 + i])
	{
		dest[i] = src[i1 + i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i1;
	size_t	i2;
	char	*zone;

	if (s1[0] == '\0')
		return (ft_strdup(""));
	i1 = 0;
	while (s1[i1] && is_in_set(s1[i1], set))
		i1++;
	i2 = i1;
	while (s1[i2])
		i2++;
	i2--;
	while (is_in_set(s1[i2], set))
	{
		if (i2 == 0)
			return (ft_strdup(""));
		i2--;
	}
	zone = malloc((i2 - i1 + 2) * sizeof(char));
	if (zone == NULL)
		return (NULL);
	copier_tab(zone, s1, i1, i2);
	return (zone);
}

char	*ft_strtrim_all(char const *s, char const *set)
{
	char	*ret;
	int		i;
	int		j;
	int		len;

	if (s[0] == '\0')
		return (ft_strdup(""));

	len = ft_strlen(s);
	ret = malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (is_in_set(s[i], set) == 0)
		{
			ret[j++] = s[i];
		}
		i++;
	}
	ret[j] = 0;
	return (ret);
}
/*
#include <stdio.h>
#include <stdlib.h>

void test3(char const *s1, char const *s2)
{
        char *sdup1 = ft_strdup(s1);
        char *sdup2 = ft_strdup(s2);
        char *ret  = ft_strtrim(sdup1, sdup2);
        printf("str:%p:%s\n", s1, s1);
        printf("str:%p:%s\n", s2, s2);
        printf("str:%p:%s\n", sdup1, sdup1);
        printf("str:%p:%s\n", sdup2, sdup2);
        printf("ret:%p:%s\n", ret, ret);

        free(sdup1);
        free(sdup2);
        free(ret);
}

int     main(int argc, char *argv[])
{
        if (argc == 3) test3(argv[1], argv[2]);
        else printf("Wrong params!");
}
*/
