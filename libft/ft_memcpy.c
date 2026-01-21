/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:54:58 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/04 17:44:27 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOC void *ft_memcpy(void *dest, const void *src, size_t n)
 * @RETOUR Copie n octets de la zone de mémoire src vers la zone de mémoire 
 * dest.  Les zones de mémoire ne doivent pas se chevaucher. 
 * Utilisez memmove(3) si les zones de mémoire se chevauchent.
 * VALEUR DE RETOUR La fonction memcpy() renvoie un pointeur sur dest.
 * @IN ft_memcpy abcdefghij ABCDEFGHIJ 5
 * @OUT ABCDEfghij
 */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL && n > 0)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void	afficher(char *str, size_t n)
{
	int i = 0;
	while (i < n)
		printf("%c", str[i++]);
	printf("\n");
}

void	test1()
{
	char  c1;
        char  c2;
        char  s1[10];
        char  s2[10];
	int   i;

        c1 = argv[1][0];      
        c2 = argv[2][0];      

        i = 0;
        memset(s1, c1, 10);
        memset(s2, c2, 10);
        memcpy(s2, s1, 5);
        afficher(s1, sizeof(s1));
        afficher(s2, sizeof(s2));

        memset(s2, c2, 10);
        ft_memcpy(s2, s1, 5);
        afficher(s1, sizeof(s1));
        afficher(s2, sizeof(s2));

}

void	test2(char *s1, char *s2, size_t i)
{
        ft_memcpy(s1, s2, i);
        afficher(s1, strlen(s1));
        afficher(s2, strlen(s2));
}

int	main(int argc, char *argv[])
{
	if (argc == 1) test1();
	if (argc == 4) test2(argv[1], argv[2], argv[3]);

}
*/
