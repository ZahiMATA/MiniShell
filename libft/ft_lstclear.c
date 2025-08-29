/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:11 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/15 17:37:30 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS void ft_lstclear(t_list **lst, void (*del)(void *));
 * @RETOUR Supprime et libère la mémoire de l’élément passé en paramètre, et 
 * de tous les éléments qui suivent, à l’aide de ’del’ et de free(3)
 * Enfin, le pointeur initial doit être mis à NULL.
 * @IN L1->L2>-L3
 * @OUT *L1 = NULL
 */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = p;
	}
}
/*
#include <stdlib.h>
#include <stdio.h>

void effacer(void *element)
{
	free(element);
}

int	*allouer(int i)
{
	int	*p;
	p = malloc(sizeof(int));
	if (p == NULL)
		return (NULL);
	*p = i;
	return p;
}

static void test(int n1, int n2, int n3)
{
        t_list *liste1 = ft_lstnew(allouer(n1));
        t_list *liste2 = ft_lstnew(allouer(n2));
        t_list *liste3 = ft_lstnew(allouer(n3));
        ft_lstadd_back(&liste1, liste2);
        ft_lstadd_back(&liste1, liste3);
	ft_lstclear(&liste1, &effacer);
        //t_list *liste = ft_lstlast(liste1);
        int n = ft_lstsize(liste1);

        if ((liste1 && liste2) || 1==0)
        {
                printf("content1=%p:%d\n", liste1, *(int *)liste1->content);
                printf("content2=%p:%d\n",
			liste1->next, *(int *)liste1->next->content);
                printf("content1=%p:%d\n", liste1, *(int *)liste1->content);
                printf("content3=%p:%d\n", liste3, *(int *)liste3->content);
                printf("content=%p:%d\n", &n, n);
                //free(liste1->next);
                //free(liste1);
        }
        else
                printf("Echec allocation");

}

int     main(int argc, char *argv[])
{
        if (argc == 4) test(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
        else printf("Wrong params!");
}
*/
