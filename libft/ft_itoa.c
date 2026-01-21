/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:00:04 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/14 15:11:56 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS char *ft_itoa(int n);
 * @RETOUR Alloue (avec malloc(3)) et retourne une chaîne de caractères 
 * représentant l’entier ’n’ reçu en argument. Les nombres négatifs doivent 
 * être gérés.
 * @IN ft_itoa -42 ; 42
 * @OUT        -42 ; 42
 */

#include <stdlib.h>
#include "libft.h"

/*
 * nb_decimal(n) : pour les positifs et negatifs
 */
static int	nb_decimal(int n)
{
	int	i;
	int	sign;

	i = 1;
	sign = 1;
	if (n < 0)
	{
		n *= -1;
		sign *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	if (sign == -1)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		nb;
	int		nb_dec;

	nb = n;
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	nb_dec = nb_decimal(nb);
	if (nb < 0)
		nb *= -1;
	ret = malloc((nb_dec + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret[nb_dec--] = '\0';
	while (nb_dec >= 0)
	{
		ret[nb_dec--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		ret[0] = '-';
	return (ret);
}
/*
#include <stdlib.h>
#include <stdio.h>

void test1(int n)
{
	char	*ret;

	ret = ft_itoa(n);
	n = nb_decimal(n);
	printf("n  :%p:%d\n", &n, n);
	printf("ret:%p:%s\n", ret, ret);
        free(ret);
}

int     main(int argc, char *argv[])
{
        if (argc == 2) test1(atoi(argv[1]));
	else printf("Wrong params!");
}*/
