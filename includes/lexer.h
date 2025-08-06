/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:18:08 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/06 14:14:28 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stddef.h>
# include <stdlib.h>

typedef enum e_token
{
	T_PIPE,
	T_REDIRECT_LEFT,
	T_REDIRECT_RIGHT,
	T_DOUBLE_REDIRECT_LEFT,
	T_DOUBLE_REDIRECT_RIGHT,
	T_STRING,
} t_token;

typedef struct s_token_list
{
	char				*val;
	t_token				token;
	struct s_token_list *next;
} t_token_list;

typedef struct s_param
{
	t_token_list	*token_list;
	t_token			token;
	char			*val;
	int				i;
	int				n;
} t_param;

t_token_list	*lex_lstnew(t_token token, char *val);
void			lex_lstadd_back(t_token_list **lst, t_token_list *new);
t_token_list 	*lexer(char *line);

#endif
