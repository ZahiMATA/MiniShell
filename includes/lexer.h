/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:18:08 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/06 19:02:31 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
//#include "minishell.h"
//# include <stddef.h>
//# include <stdlib.h>

# ifndef DEBUG_LEX
#  define DEBUG_LEX 1
# endif
# define ERROR_NOTCLOSEDSTRING "Syntax error: String must be closed"

typedef struct s_minishell t_minishell;

typedef enum e_token
{
	T_PIPE,
	T_REDIRECT_LEFT,
	T_REDIRECT_RIGHT,
	T_DOUBLE_REDIRECT_LEFT,
	T_DOUBLE_REDIRECT_RIGHT,
	T_STRING,
	T_WORD,
} t_token;

typedef struct s_token_list
{
	char				*val;
	t_token				token;
	struct s_token_list *next;
} t_token_list;

typedef struct s_param
{
	t_minishell		*m;
	//t_token_list	*token_list;
	int				i;
	char			*line;
	//int				ret;
} t_param;

void			debug_show_tokens(t_minishell *m);
t_token_list	*lex_lstnew(t_token token, char *val);
void			lex_lstadd_back(t_token_list **lst, t_token_list *new);
void			lex_lstclear(t_token_list **lst);
void		 	lexer(t_minishell *m, char *line);
int				ft_islexer(int c);

#endif
