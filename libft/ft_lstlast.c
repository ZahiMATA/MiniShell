/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:28:40 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/15 13:48:48 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS t_list *ft_lstlast(t_list *lst);
 * @RETOUR Renvoie le dernier élément de la liste.
 * @IN L1->L2
 * @OUT L1
 */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
	{
		lst = lst -> next;
	}
	return (lst);
}
/*
#include <stdlib.h>
#include <stdio.h>
static void test(int n1, int n2)
{
	t_list *liste1 = ft_lstnew(&n1);
	t_list *liste2 = ft_lstnew(&n2);
	ft_lstadd_front(&liste1, liste2);
	int n = ft_lstsize(liste1);
	t_list *liste3 = ft_lstlast(liste1);

	if (liste1 && liste2)
	{
		printf("content1=%p:%d\n", liste1, *(int *)liste1->content);
		printf("content2=%p:%d\n", liste1->next, *(int *)liste1->next->content);
		printf("content3=%p:%d\n", liste3, *(int *)liste3->content);
		printf("content=%p:%d\n", &n, n);
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
