/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:50:31 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/04 19:32:53 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOC ft_strdup
 * @RETOUR Renvoie un pointeur sur une nouvelle chaîne qui est un double de la
 * chaîne s. La mémoire pour la nouvelle chaîne est ob tenue avec malloc,
 *  et peut être libérée avec free.
 * VALEUR DE RETOUR  En cas de succès, la fonction strdup() renvoie un pointeur
 * sur la chaîne dupliquée.  Elle renvoie NULL si la mémoire disponible est
 * insuffisante et errno indique la cause de l'erreur.
 * @IN ft_strdup "abc"
 * @OUT "abc
 */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*zone;
	size_t	len;

	len = ft_strlen(s);
	zone = malloc((len + 1) * sizeof(char));
	if (zone == NULL)
		return (NULL);
	zone[len] = '\0';
	while (len--)
		zone[len] = s[len];
	return (zone);
}
