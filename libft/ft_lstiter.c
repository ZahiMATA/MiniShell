/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:41:20 by ybouroga          #+#    #+#             */
/*   Updated: 2025/05/15 18:23:33 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS void ft_lstiter(t_list *lst, void (*f)(void *));
 * @RETOUR Itère sur la liste ’lst’ et applique la fonction ’f’ au contenu 
 * chaque élément.
 * @IN ft_lstiter L1(10)->L2(13)->L(14)
 * @OUT 10 13 14
 */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst -> content);
		lst = lst->next;
	}
}
/*
#include <stdlib.h>
#include <stdio.h>

void f_aff (int *n)
{
	printf("n=%d\n", *n);
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
        ft_lstiter(liste1, (void *)&f_aff);
	
}

int     main(int argc, char *argv[])
{
        if (argc == 4) test(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
        else printf("Wrong params!");
}
*/
