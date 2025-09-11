/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:23:17 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/11 15:11:45 by ybouroga         ###   ########.fr       */
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

static void	lexer_subquote(t_param *_, int offset)
{
	_->start = _->i;
	_->i += offset;
	while (_->m->line[_->i] &&  _->m->line[_->i] != '\'')
	{
		if (ft_strncmp(_->m->line + _->i, "\\\"", 2) == 0)
			_->i++;
		_->i++;
	}
}

static void lexer_subword(t_param *_, int offset)
{
	_->open_q = 0;
	_->start = _->i;
	_->i += offset;
	while (_->m->line[_->i])
	{
		if (_->m->line[_->i] == '"' && _->open_q == 0)
			_->open_s = !_->open_s;
		else if (_->m->line[_->i] == '\'' && _->open_s == 0)
			_->open_q = !_->open_q;
		else if (ft_strncmp(_->m->line + _->i, "\\\"", 2) == 0)
			_->i++;
		else if (ft_strncmp(_->m->line + _->i, "\\'", 2) == 0)
			_->i++;
		else if (_->open_q == 0 && _->open_s == 0 && ft_issublexer(_->m->line[_->i]))
			break;
		_->i++;
	}
}

static void	lexer_quote(t_param *_, int offset)
{
	char	*s;

	_->open_s = 0;
	while (_->m->line[_->i])
	{
		lexer_subquote(_, offset);
		if (_->m->line[_->i] == '\0')
		{
			ft_return_error(_->m, ERROR_SYNTAX, ERROR_QUOTENOTCLOSED, EXIT_FAILURE);
			lex_lstclear(&_->m->token_list);
			return;
		}
		break;
		printf("[%d]:[%c]\n", _->i, _->m->line[_->i]);
		//_->i++;
		printf("[%d]:[%c]\n", _->i + 1, _->m->line[_->i + 1]);
		if (_->m->line[_->i + 1] == 0)
		{
			break;
		}
		debug_var("NOB");
		if (_->m->line[_->i + 1] == '\'')
		{
			_->i++;
			break;
		}
		lexer_subword(_, 0);
		// if (_->open_q != 0 || _->open_s != 0)
		// {
		// 	ft_return_error(_->m, ERROR_SYNTAX, ERROR_STRINGNOTCLOSED, EXIT_FAILURE);
		// 	lex_lstclear(&_->m->token_list);
		// 	return ;
		// }
		//_->i++;
		//offset = 1;
	}
	s = ft_substring(_->m->line, _->start , (_->i - _->start) + 1);
	if (s == NULL)
		ft_exit_fail_status(_->m, NULL, EXIT_ALLOC_ERROR);
	add_token(_, T_WORD, s, 0);
	_->i++;
	mem_free(s, "lexer_string.s", s);
}

static void lexer_word(t_param *_, int offset)
{
	char	*s;

	_->open_s = 0;
	lexer_subword(_, offset);
	if (_->open_q != 0 || _->open_s != 0)
	{
		ft_return_error(_->m, ERROR_SYNTAX, ERROR_STRINGNOTCLOSED, EXIT_FAILURE);
		lex_lstclear(&_->m->token_list);
		return ;
	}
	s = ft_substring(_->m->line, _->start, _->i - _->start);
	if (s == NULL)
		ft_exit_fail_status(_->m, NULL, EXIT_ALLOC_ERROR);
	add_token(_, T_WORD, s, 0);
	mem_free(s, "lexer_word", s);
}

void	lexer(t_minishell *m)
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
			lexer_quote(&_, 1);
		else
			lexer_word(&_, 0);
	}
}
