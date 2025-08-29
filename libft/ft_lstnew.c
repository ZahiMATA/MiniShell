/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:23:26 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/15 11:15:22 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS t_list *ft_lstnew(void *content);
 * @RETOUR Alloue (avec malloc(3)) et renvoie un nouvel élément. La variable 
 * membre ’content’ est initialisée à l’aide de la valeur du paramètre 
 * ’content’. La variable ’next’ est initialisée à NULL.
 * @IN
 * @OUT
 */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*liste;

	liste = malloc(sizeof(t_list));
	if (liste == NULL)
		return (NULL);
	liste -> content = content;
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
