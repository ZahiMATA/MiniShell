/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:23:17 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/11 15:28:49 by ybouroga         ###   ########.fr       */
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

static void	lexer_string(t_param *_)
{
	char	*s;
	int		start;
	int		len;

	_->i++;
	len = 0;
	start = _->i;
	while (_->line[_->i] && _->line[_->i] != '"')
	{
		len++;
		_->i++;
	}
	if (_->line[_->i] == '\0')
	{
		ft_return_error(_->m, ERROR_NOTCLOSEDSTRING, EXIT_FAILURE);
		lex_lstclear(&_->m->token_list);
		return ;
	}
	s = ft_substring(_->line, start, len);
	if (!s)
		ft_exit_fail_status(_->m, NULL, EXIT_ALLOC_ERROR);
	add_token(_, T_STRING, s, 0);
	_->i++;
	free(s);
}

static void	lexer_single_quote(t_param *_)
{
	char	*s;
	int		start;
	int		len;

	_->i++;
	len = 0;
	start = _->i;
	while (_->line[_->i] && _->line[_->i] != '\'')
	{
		len++;
		_->i++;
	}
	if (_->line[_->i] == '\0')
	{
		ft_return_error(_->m, ERROR_NOTCLOSEDSTRING, EXIT_FAILURE);
		lex_lstclear(&_->m->token_list);
		return ;
	}
	s = ft_substring(_->line, start, len);
	if (!s)
		ft_exit_fail_status(_->m, NULL, EXIT_ALLOC_ERROR);
	add_token(_, T_STRING, s, 0);
	_->i++;
	free(s);
}

/* A voir semble fonctionnel sans
static void	lexer_word(t_param *_)
{
	char	*s;
	int		start;
	int		len;

	len = 0;
	start = _->i;
	while (_->line[_->i]
		&& _->line[_->i] != '|'
		&& _->line[_->i] != '<'
		&& _->line[_->i] != '>'
		&& _->line[_->i] != '\''
		&& _->line[_->i] != '"'
		&& !ft_isspace(_->line[_->i]))
	{
		// stop si espace suivi d’un séparateur
		if (ft_isspace(_->line[_->i])
			&& (_->line[_->i + 1] == '<'
				|| _->line[_->i + 1] == '>'
				|| _->line[_->i + 1] == '|'))
			break ;
		len++;
		_->i++;
	}
	s = ft_substring(_->line, start, len);
	if (!s)
		ft_exit_fail_status(_->m, NULL, EXIT_ALLOC_ERROR);
	add_token(_, T_WORD, s, 0);
	free(s);
}*/

static void lexer_word(t_param *_)
{
	char	*s;
	int		start;
	int		len;

	len = 0;
	start = _->i;
	while (_->line[_->i] && !ft_islexer(_->line[_->i]))
	{
		len++;
		_->i++;
	}
	s = ft_substring(_->line, start, len);
	if (s == NULL)
		ft_exit_fail_status(_->m, NULL, EXIT_ALLOC_ERROR);
	add_token(_, T_WORD, s, 0);
	free(s);
}

void	lexer(t_minishell *m, char *line)
{
	t_param	_;

	_.m = m;
	_.i = 0;
	_.line = line;
	while (m->last_status == EXIT_SUCCESS && line && line[_.i])
	{
		while (ft_isspace(line[_.i]))
			_.i++;
		if (line[_.i] == '\0')
			break ;
		else if (line[_.i] == '|')
			add_token(&_, T_PIPE, "|", 1);
		else if (line[_.i] == '<' && line[_.i + 1] == '<')
			add_token(&_, T_DOUBLE_REDIRECT_LEFT, "<<", 2);
		else if (line[_.i] == '>' && line[_.i + 1] == '>')
			add_token(&_, T_DOUBLE_REDIRECT_RIGHT, ">>", 2);
		else if (line[_.i] == '<')
			add_token(&_, T_REDIRECT_LEFT, "<", 1);
		else if (line[_.i] == '>')
			add_token(&_, T_REDIRECT_RIGHT, ">", 1);
		else if (line[_.i] == '"')
			lexer_string(&_);
		else if (line[_.i] == '\'')
			lexer_single_quote(&_);
		else
			lexer_word(&_);
	}
}
