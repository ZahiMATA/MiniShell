/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:01:03 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/15 16:41:36 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* @CDOC ft_strncmp
 * @RETOUR Compare que les n premiers octets (au maximum) de s1 et s2.
 * Renvoit un nombre entier inférieur, égal ou supérieur à  zéro si  les n
 * premiers octets de s1 est inférieur, égal, ou supérieur à s2.
 * @IN ft_strncmp a2 a1 2
 * @OUT 1
 * @IN ft_strncmp a2 a1 1
 * @OUT 0
 * @IN ft_strncmp b a 0
 * @OUT 0
 * @IN ft_strncmp  \200 \0 1
 * @OUT 128
 */

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	if (n <= 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp_s2len(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s2)));
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void	test(char *s1, char *s2, int n)
{
	int	i;
        i = strncmp(s1, s2, n);
        printf("%p:%d\n", &i, i);

	i = ft_strncmp(s1, s2, n);
	printf("%p:%d\n", &i, i);
}

int	main(int argc, char *argv[])
{
	if (argc == 2) test("\200", "\0", atoi(argv[1]));
	if (argc == 3) test(argv[1], "\0", atoi(argv[2]));
	if (argc == 4) test(argv[1], argv[2], atoi(argv[3]));
	return 0;
}
*/
