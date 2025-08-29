/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:02:57 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/15 17:02:18 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS void ft_lstdelone(t_list *lst, void (*del)(void *))
 * @RETURN lst: L’élément à free del: L’adresse de la fonction permettant de
 * supprimer le contenu de l’élément.
 * Libère la mémoire de l’élément passé en argument en utilisant la fonction 
 * ’del’ puis avec free(3). La mémoire de ’next’ ne doit pas être free.
 * @IN L1->L2->L3 L2
 * @OUT L2->content et L2 free 
 */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst -> content);
	free(lst);
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
	ft_lstdelone(liste2, &effacer);
        //t_list *liste = ft_lstlast(liste1);
        int n = ft_lstsize(liste1);

        if (liste1 && liste2)
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
