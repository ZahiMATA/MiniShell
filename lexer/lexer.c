/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:23:17 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/11 12:32:58 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  < makefile "tr a A" | "tr b B" > ficout
// -> **token  [<][makefile][tr a A][|][tr b B][>][ficout]
#include "minishell.h"

static void	add_token(t_param *_, t_token token, char *val, int len)
{
	t_token_list	*tmp;

	tmp = lex_lstnew(token, val);
	if (tmp == NULL)
		ft_exit_fail_status(_->m, NULL, EXIT_ALLOC_ERROR);
	lex_lstadd_back(&_->m->token_list, tmp);
	_->i += len;
}

void	lexer_subquote(t_param *_, char c, int offset)
{
	//char	*s;
	//int		start;
	// int		open_q;
	// int		open_s;

	// open_q = 0;
	// open_s = 0;
	_->start = _->i;
	_->i += offset;
	while (_->m->line[_->i] &&  _->m->line[_->i] != c)
	{
		/*if (_->m->line[_->i] == '"' && open_q == 0)
			open_s = !open_s;
		else if (_->m->line[_->i] == '\'' && open_s == 0)
			open_q = !open_q;*/
		if (ft_strncmp(_->m->line + _->i, "\\\"", 2) == 0)
			_->i++;
		_->i++;
	}
}

 void	lexer_quote(t_param *_, char c, int offset)
{
	char	*s;
	//int		start;

	lexer_subquote(_, c, offset);
	if (_->m->line[_->i] == '\0')
	{
		ft_return_error(_->m, ERROR_SYNTAX, ERROR_STRINGNOTCLOSED, EXIT_FAILURE);
		lex_lstclear(&_->m->token_list);
		return;
	}

	s = ft_substring(_->m->line, _->start , (_->i - _->start) + 1);
	if (s == NULL)
		ft_exit_fail_status(_->m, NULL, EXIT_ALLOC_ERROR);
	add_token(_, T_WORD, s, 0);
	_->i++;
	mem_free(s, "lexer_string.s", s);
}

/*static*/ void lexer_word(t_param *_, char c, int offset)
{
	char	*s;
	int		start;
	int		open_q;
	int		open_s;

	(void)c;
	open_q = 0;
	open_s = 0;
	start = _->i;
	_->i += offset;
	while (_->m->line[_->i])
	{
		if (_->m->line[_->i] == '"' && open_q == 0)
			open_s = !open_s;
		else if (_->m->line[_->i] == '\'' && open_s == 0)
			open_q = !open_q;
		else if (ft_strncmp(_->m->line + _->i, "\\\"", 2) == 0)
			_->i++;
		else if (ft_strncmp(_->m->line + _->i, "\\'", 2) == 0)
			_->i++;
		else if (open_q == 0 && open_s == 0 && ft_issublexer(_->m->line[_->i]))
			break;
		_->i++;
	}
	if (open_q != 0 || open_s != 0)
	{
		ft_return_error(_->m, ERROR_SYNTAX, ERROR_STRINGNOTCLOSED, EXIT_FAILURE);
		lex_lstclear(&_->m->token_list);
		return ;
	}
	s = ft_substring(_->m->line, start, _->i - start);
	if (s == NULL)
		ft_exit_fail_status(_->m, NULL, EXIT_ALLOC_ERROR);
	add_token(_, T_WORD, s, 0);
	mem_free(s, "lexer_word", s);
}

void	lexer(t_minishell *m/*, char *line*/)
{
	t_param	_;

	_.m = m;
	_.i = 0;
	while (m->last_status == EXIT_SUCCESS && m->line && m->line[_.i])
	{
		while (ft_isspace(m->line[_.i]))
			_.i++;
		if (m->line[_.i] == '\0')
			break ;
		else if (m->line[_.i] == '|')
			add_token(&_, T_PIPE, "|", 1);
		else if (m->line[_.i] == '<' && m->line[_.i + 1] == '<')
			add_token(&_, T_DOUBLE_REDIRECT_LEFT, "<<", 2);
		else if (m->line[_.i] == '>' && m->line[_.i + 1] == '>')
			add_token(&_, T_DOUBLE_REDIRECT_RIGHT, ">>", 2);
		else if (m->line[_.i] == '<')
			add_token(&_, T_REDIRECT_LEFT, "<", 1);
		else if (m->line[_.i] == '>')
			add_token(&_, T_REDIRECT_RIGHT, ">", 1);
		else if (m->line[_.i] == '\'')
			lexer_quote(&_, m->line[_.i], 1);
		else
			lexer_word(&_, m->line[_.i], 0);
	}
}
