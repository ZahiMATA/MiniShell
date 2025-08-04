/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:05:08 by ybouroga          #+#    #+#             */
/*   Updated: 2025/07/01 16:32:37 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOC
 * @RETOUR La fonction strlen() renvoie le nombre d'octets de la chaîne de
 * caractères pointée par s.
 * @IN ft_strlen.c ABC
 * @OUT 3
 */

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	char *s;

	s = "hello";
	printf("%lu:%zu", strlen(s), ft_strlen(s));
}*/
