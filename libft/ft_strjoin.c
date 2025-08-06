/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:50:06 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/06 21:01:33 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS char *ft_strjoin(char const *s1, char const *s2);
 * @RETOUR Alloue (avec malloc(3)) et retourne une nouvelle chaîne, résultat
 * de la concaténation de s1 et s2.
 * @IN ft_strjoin "abc" "def"
 * @OUT "abcdef"
 *
 * ft_strjoin(char const *s1, char const *s2)
 * -> ft_strjoin_with_char(char const *s1, char c, char const *s2)
 */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*zone;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	zone = malloc((len1 + len2 + 1) * sizeof(char));
	if (zone == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		zone[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		zone[i + len1] = s2[i];
		i++;
	}
	zone[len1 + len2] = '\0';
	return (zone);
}

char	*ft_strjoin_with_char(char const *s1, char c, char const *s2)
{
	char	*zone;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	zone = malloc((len1 + len2 + 2) * sizeof(char));
	if (zone == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		zone[i] = s1[i];
		i++;
	}
	zone[i++] = c;
	i = 0;
	while (i < len2)
	{
		zone[i + len1 + 1] = s2[i];
		i++;
	}
	zone[len1 + len2 + 1] = '\0';
	return (zone);
}
/*
#include <stdio.h>
#include <stdlib.h>

void test1(char *s, int n)
{
	int i = 0;
	while (i < n)
	{
		printf("%c:%d\n", s[i], i);
		i++;
	}
}
void test4(char const *s1, char const *s2)
{
        char *sdup1 = ft_strdup(s1);
        char *sdup2 = ft_strdup(s2);
	char *ret  = ft_strjoin(sdup1, sdup2);
	printf("str:%p:%s\n", s1, s1);
	printf("str:%p:%s\n", s2, s2);
	printf("str:%p:%s\n", sdup1, sdup1);
	printf("str:%p:%s\n", sdup2, sdup2);
	printf("ret:%p:%s\n", ret, ret);

	free(sdup1);
	free(sdup2);
	free(ret);
}

int	main(int argc, char *argv[])
{
	if (argc == 1) test1("A\0B", 20);
	else if (argc == 3) test4(argv[1], argv[2]);
	else printf("Wrong params!");
}*/
