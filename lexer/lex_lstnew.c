/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:41:06 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/06 17:56:58 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_token_list	*lex_lstnew(t_token token, char *val)
{
	t_token_list	*liste;
	char			*value;

	liste = malloc(sizeof(t_token_list));
	if (liste == NULL)
		return (NULL);
	value = ft_strdup(val);
	if (value == NULL)
		return (NULL);
	liste->token = token;
	liste-> val = value;
	liste-> next = NULL;
	return (liste);
}

