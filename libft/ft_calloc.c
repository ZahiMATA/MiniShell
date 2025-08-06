/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:15:22 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/06 21:02:07 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOC ft_calloc
 * @ RETOUR Alloue de la mémoire pour un tableau d'éléments nmemb de size
 * octets chacun et renvoie un pointeur sur la mémoire allouée. La mémoire est
 * mise à zéro.  Si nmemb ou size est égal à 0, calloc() renvoie soit NULL,
 * soit une valeur de pointeur unique qui peut plus tard être passée avec
 * succès à free().  Si la multiplication de nmemb et de size entraîne un
 * dépassement d'entier, calloc() renvoie une erreur.  En revanche, un
 * dépassement d'entier ne serait pas détecté lors de l'appel suivant à
 * malloc(), ce qui aurait pour conséquence d'allouer un bloc de mémoire de
 * taille incorrecte à l'adresse
 * VALEUR DE RETOUR Renvoit un pointeur sur la mémoire allouée, qui est
 * correctement alignée pour tout type intégré.En cas d'erreur, cette
 * fonction renvoit NULL.  NULL peut également être renvoyé par un appel
 * réussi à calloc() avec nmemb ou une taille égale à zéro.
 * @IN ft_calloc
 * OUT (void *)
 */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*zone;

	zone = malloc(nmemb * size);
	if (zone == NULL)
		return (NULL);
	ft_bzero(zone, nmemb * size);
	return (zone);
}
