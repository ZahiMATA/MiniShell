/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:13:07 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/15 13:25:48 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS int ft_lstsize(t_list *lst);
 * @RETOUR lst: Le début de la liste. Compte le nombre d’éléments de la liste.
 * @IN L1->L2
 * @OUT 2
 */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
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

	if (liste1 && liste2)
	{
		printf("content=%p:%d\n", liste1, *(int *)liste1->content);
		printf("content=%p:%d\n", liste1->next, *(int *)liste1->next->content);
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
