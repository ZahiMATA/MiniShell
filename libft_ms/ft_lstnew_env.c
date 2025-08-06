/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:23:26 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/06 20:33:08 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS t_list *ft_lstnew(void *content);
 * @RETOUR Alloue (avec malloc(3)) et renvoie un nouvel élément. La variable
 * membre ’content’ est initialisée à l’aide de la valeur du paramètre
 * ’content’. La variable ’next’ est initialisée à NULL.
 * @IN
 * @OUT
 */

#include "minishell.h"

t_env	*ft_lstnew_env(void *key, void *val)
{
	t_env	*liste;

	liste = malloc(sizeof(t_env));
	if (liste == NULL)
		return (NULL);
	liste -> key = key;
	liste -> val = val;
	liste -> next = NULL;
	return (liste);
}
/*
#include <stdlib.h>
#include <stdio.h>
static void test1(int n)
{
	t_list *liste = ft_lstnew(&n);
	if (liste)
	{
		printf("content=%p:%p:%d\n", liste,
		(int *)liste->content, *(int *)liste->content);
		printf("next=%p\n", liste->next);
	}
	else
		printf("echecs allocation");
}

int     main(int argc, char *argv[])
{
        if (argc == 2) test1(atoi(argv[1]));
	else printf("Wrong params!");
}*/
