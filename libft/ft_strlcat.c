/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:17:23 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/04 11:01:56 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOC size_t ft_strlcat(char *dst, const char *src, size_t siz)
 * @RETOUR Concatène deux chaînes de caractères. Ajoute src à la chaîne dst de 
 * taille siz. siz est la taille totale de dst
 * Au plus siz-1 caractères seront copiés. 
 * Se termine toujours par NULL (sauf si siz <= strlen(dst)).
 * Retour 
 * La fonction strlcat() retourne strlen(src) + MIN(siz, strlen(dst initial)). 
 * Si retval >= siz, une troncature s'est produite.
 * @IN ft_strlcat "01234" "abcdeFGHIJ" 16
 * @OUT 15 (01234abcdeFGHIJ) 
 * @IN ft_strlcat "01234" "abcdeFGHIJ" 15
 * @OUT 15 (01234abcdeFGHI\0) 
 * @IN ft_strlcat "01234" "abcdeFGHIJ" 7
 * @OUT 15 (01234a)
 * @IN ft_strlcat "01234" "abcdeFGHIJ" 5
 * @OUT 15 (01234)
 * @IN ft_strlcat "01234" "abcdeFGHIJ" 4
 * @OUT 14 (01234)
 * @IN ft_strlcat "01234" "abcdeFGHIJ" 0
 * @OUT 10 (01234)
*/

#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a >= b)
		return (b);
	else
		return (a);
}

size_t	ft_strlcat(char *dst, const char *src, size_t siz)

{
	size_t	i;
	size_t	ld;
	size_t	ls;

	ld = 0;
	ls = 0;
	while (dst[ld])
		ld++;
	while (src[ls])
		ls++;
	i = 0;
	while (src[i] && (i + ld -(-1) < siz - 0))
	{
		dst[ld + i] = ((char *)src)[i];
		i++;
	}
	dst[i + ld] = '\0';
	return (ls + ft_min(siz, ld));
}
/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void	afficher(char *str, size_t n)
{
	size_t	i = 0;
	while (str[i] && i < n)
		printf("%c", str[i++]);
	printf("\n");
}
void	init_inc(char *str, char c, size_t n)
{
	size_t i = 0;
	while (i < n)
	{
		str[i] = i + c;
		i++;
	}
}

void	test1()
{
	//char	c1;
	//char	c2;
	char	s1[10] = "01234";
        char    s2[20] = "abcdeFGHIJ";
	int	i;

	printf("(s1)=%lu:(s2)=%lu\n", sizeof(s1), sizeof(s2));
	i = ft_strlcat(s1, s2, sizeof(s1));
	printf("i=%d\n", i);	
	afficher(s1, sizeof(s1));
        afficher(s2, sizeof(s2));

}

void test2(char *s1, char *s2, int n)
{
	char buffer[n];
	
	int l = 0;
	while (s1[l])
	{	buffer[l] = s1[l];
		l++;
	}
	buffer[l] = '\0';
	int i = ft_strlcat(buffer, s2, n);
	printf("s1=%s\ns2=%s\ni=%d\n", buffer, s2, i);
}

int     main(int argc, char *argv[])
{
	if (argc == 1) test1();
	if (argc == 4) test2(argv[1], argv[2], atoi(argv[3]));

}
*/
