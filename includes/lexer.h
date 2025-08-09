/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:18:08 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/09 16:20:50 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
//#include "minishell.h"
# include <stddef.h>
//# include <stdlib.h>

# ifndef DEBUG_LEX
#  define DEBUG_LEX 1
# endif
# define ERROR_NOTCLOSEDSTRING "Syntax error: String must be closed"
# define ERROR_NL "Syntax error near unexpected token `newline'"
# define RETURN_NL 2

typedef struct s_minishell	t_minishell;
typedef struct s_cmd2		t_cmd2;

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

// [input <] [output >] [heredoc <<] [append >>]
typedef enum e_redirect
{
	T_NONE,
	T_INPUT,
	T_OUTPUT,
	T_HEREDOC,
	T_APPEND,
} t_redirect;

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
void			debug_serial_token(t_minishell *m, char *buffer, size_t size);
void			debug_show_cmds(t_minishell *m);
t_token_list	*lex_lstnew(t_token token, char *val);
void			lex_lstadd_back(t_token_list **lst, t_token_list *new);
void			lex_lstclear(t_token_list **lst);
void		 	lexer(t_minishell *m, char *line);
int				ft_islexer(int c);
void			parser(t_minishell *m);
int 			ft_is_stringword(t_minishell *m);

#endif
