/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 20:25:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/06 20:27:16 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:54:58 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/04 17:05:19 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOC void ft_bzero(void *s, size_t n)
 * @RETOUR La fonction bzero() efface les données des n octets de la mémoire
 * commençant à l'emplacement indiqué par s, en écrivant des zéros
 * (octets contenant '\0') dans cette zone.
 * @IN ft_bzero.c ABCDEFGHIJ 5
 * @OUT \0\0\0\0\0FGHIJ
 */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = '\0';
}
/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void aff(char *s, int n)
{
	int i = 0;
	while (i < n)
	{
		printf("[%c:%d]", s[i], s[i]);
		i++;
	}
	printf("%c", '\n');
}

int	main(int argc, char *argv[])
{
	char	c;
	char	s1[10];
	char	s2[10];
	int	i;
	int	n;

	n = atoi(argv[2]);
	printf("argv[1]=%s:len=%lu\n", argv[1], strlen(argv[1]));
	ft_bzero(argv[1], n);
	printf("argv[1]=%s:len=%lu\n", argv[1], strlen(argv[1]));
	aff(argv[1],10);
	//c = argv[1][0];
	//i = 0;
	//ft_bzero(s1, 10);
	//bzero(s2, 10);
	//while (i < 10)
	//{
	//	printf("%d:%d:%d:%c\n", i, s1[i], s2[i], s1[i]);
	//	i++;
	//}
}*/
