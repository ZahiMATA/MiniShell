/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:52:47 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/16 12:55:10 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS Itère sur la liste ’lst’ et applique la fonction ’f ’au contenu de 
 * chaque élément. Crée une nouvelle liste résultant des applications 
 * successives de ’f’. La fonction ’del’ est là pour détruire le contenu d’un 
 * élément si nécessaire.
 * @IN ft_lstiter L1(10)->L2(13)->L(14)
 * @OUT L1(100)->L2(169)->L(196)
 */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*p;
	void	*fx;

	ret = NULL;
	while (lst)
	{
		fx = f(lst -> content);
		if (fx == NULL)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		p = ft_lstnew(fx);
		if (p == NULL)
		{
			del(fx);
			ft_lstclear(&ret, del);
			return (NULL);
		}
		ft_lstadd_back(&ret, p);
		lst = lst -> next;
	}
	return (ret);
}
/*
#include <stdlib.h>
#include <stdio.h>

int	*f_carre (int *n)
{
	return allouer(*n);
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
        int	*i1;
	int	*i2;
	int	*i3;
	i1 = allouer(n1);
	i2 = allouer(n2);
	i3 = allouer(n3);
	if (!n1 || !n2 || !n3)
	{
		printf("Echec allocation");
		return;
	}
	t_list *liste1 = ft_lstnew(allouer(n1));
        t_list *liste2 = ft_lstnew(allouer(n2));
        t_list *liste3 = ft_lstnew(allouer(n3));
	ft_lstadd_back(&liste1, liste2);
        ft_lstadd_back(&liste1, liste3);
        t_list liste4 = ft_lstmap(liste1, (void *)&f_carre);
	if (liste4 == NULL)
		        if (!n1 || !n2 || !n3)
        {
                printf("Echec allocation");
                return;
        }
	

}

int     main(int argc, char *argv[])
{
        if (argc == 4) test(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
        else printf("Wrong params!");
}
*/
