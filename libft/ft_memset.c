/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:54:58 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/04 16:54:28 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOC void *ft_memset(void *s, int c, size_t n)
 * @RETOUR La fonction memset() remplit les n premiers octets de la zone de 
 * mémoire désignée par s avec l'octet constant c.
 * La fonction memset() renvoie un pointeur sur la zone de mémoire s.
 * @IN ft_memset ABCDEFGHIJ z 5
 * @OUT zzzzzFGHI
 */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = (unsigned char)c;
	return (s);
}
/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void aff(char *s, int n)
{
	int i = 0;
	while (i < n)
		printf("%c", s[i++]);
	printf("%c", '\n');
}
int	main(int argc, char *argv[])
{
	char	c;
	int	n;
	int	i;

        c = argv[2][0];
        n = atoi(argv[3]);

        //aff(argv[0],1024);
	//ft_memset(argv[0], c, 512);
	//aff(argv[0],1024);

        printf("argv[1]=%s:%lu\n", argv[1], strlen(argv[1]));
        aff(argv[1],strlen(argv[1]));

	ft_memset(argv[1], c, n);
	printf("memeset=%s\n", argv[1]);
	aff(argv[1],strlen(argv[1]));
}*/
