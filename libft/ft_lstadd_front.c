/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:17:47 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/15 13:11:07 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @ CDOCS void ft_lstadd_front(t_list **lst, t_list *new);
 * @ RETOUR lst: L’adresse du pointeur vers le premier élément de la liste.
 * new: L’adresse du pointeur vers l’élément à rajouter à la liste 
 * Ajoute l’élément ’new’ au début de la liste.
 * @IN  l1 et l2
 * @OUT l1->l2
 */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}
/*
#include <stdlib.h>
#include <stdio.h>
static void test(int n1, int n2)
{
	t_list *liste1 = ft_lstnew(&n1);
	t_list *liste2 = ft_lstnew(&n2);
	ft_lstadd_front(&liste1, liste2);
	
	if (liste1 && liste2)
	{
		printf("content=%p:%d\n", liste1, *(int *)liste1->content);
		printf("content=%p:%d\n", liste1->next, *(int *)liste1->next->content);
		free(liste1->next);
		free(liste1);
	}
	else
		printf("Echec allocation");
	}

int     main(int argc, char *argv[])
{
        if (argc == 3) test(atoi(argv[1]), atoi(argv[2]));
	else printf("Wrong params!");
}
*/
