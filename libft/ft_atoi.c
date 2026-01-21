/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:02 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/06 11:10:05 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOC ft_atoi
 * @RETOUR convertit la partie initiale de la chaîne de caractères contenue 
 * dans nptr en un entier long selon à la base donnée, qui doit être comprise 
 * entre 2 et 36 inclus, ou à la valeur spéciale 0.
 * La chaîne peut commencer par une quantité arbitraire d'espace blanc 
 * (déterminée par isspace), suivie d'un signe '+' ou '-' facultatif.  Si la 
 * base est zéro ou 16, la chaîne peut alors inclure un "0x" ou "0X" avant  fix, 
 * et le nombre sera lu en base 16 ; sinon, une base zéro est considérée comme 
 * 10 (décimal) à moins que le caractère suivant soit "0", auquel cas il est 
 * considéré comme 8 (octal).Le reste de la chaîne est converti en valeur 
 * longue de la manière habituelle, en s'arrêtant au premier caractère qui 
 * n'est pas un chiffre valide dans la base donnée.  (Dans les bases 
 * supérieures à 10, la lettre 'A' en  majuscule ou minuscule représente 10, 
 * 'B' représente 11, et ainsi de suite, avec 'Z' représentant 35).Si endptr 
 * n'est pas NULL, strtol() stocke l'adresse du premier caractère invalide dans
 * *endptr.  S'il n'y avait aucun chiffre, strtol() stocke la valeur originale 
 * de nptr dans *endptr (et renvoie 0).En par ticulier, si *nptr n'est pas '\0'
 * mais que **endptr est '\0' au retour, la chaîne entière est valide.
 * VALEUR DE RETOUR  La valeur convertie ou 0 en cas d'erreur.
 * @IN ft_atoi -42 0 42 \t84  2147483648  2147483647 -2147483648 -2147483649
 * @OUT        -42 0 42 84   -2147483648  2147483647 -2147483648  2147483647
 * @IN ft_atoi 9223372036854775808 -9223372036854775809
 * @OUT        -1                  0
 */

static	int	iswhitespace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	tests_aux_limites(unsigned long n, int sign)
{
	unsigned long	max;

	max = ((unsigned long) - 1) / 2;
	if (n >= max && sign == 1)
		return (-1);
	if (n > max && sign == -1)
		return (0);
	return (n);
}

int	ft_atoi(const char *nptr)
{
	int				i;
	int				sign;
	unsigned long	n;

	i = 0;
	sign = 1;
	n = 0;
	while (iswhitespace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i++] == '-')
			sign = -1;
	}
	while (ft_isdigit(nptr[i]))
	{
		n = (10 * n + (nptr[i] - '0'));
		i++;
	}
	n = tests_aux_limites(n, sign);
	return (n * sign);
}
/*
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	test()
{
}

int	main(int argc, char *argv[])
{
	printf("max lu=%lu\n",  ( (unsigned long)-1)/2 ) ;
	printf("max li=%li\n",  ( (unsigned long)-1)/2 ) ;
	if (argc == 3) test();
	if (argc == 1) printf("%d:%d",ft_atoi("\t12345"), atoi("\t12345"));
	else if (argc == 2) printf("atoi = %d\nft_a = %d\n", 
	atoi((argv[1])),ft_atoi((argv[1])));
	else printf("WRONG PARAM");
}
*/
