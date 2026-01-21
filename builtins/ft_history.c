/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:37:41 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 14:35:47 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int		is_numeric(const char *s);
t_list	*lst_last(t_list *lst);
void	print_history_from(t_list *lst, int start_index);
int		history_parse_validate(t_minishell *m, char **tok, int *argc, int *n);
int		history_parse_number(t_minishell *m, char **tok, int *n);

void	ft_add_history(t_minishell *m, char *s)
{
	t_list	*lst;
	char	*line;

	add_history(s);
	line = ft_strdup(s);
	if (line == NULL)
		ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
	lst = ft_lstnew(line);
	if (lst == NULL)
	{
		free(line);
		ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
	}
	ft_lstadd_back(&m->history, lst);
}

static int	parse_tokens(t_minishell *m, char **tok, int *n)
{
	int	argc;

	if (history_parse_validate(m, tok, &argc, n))
		return (1);
	if (*n == -1)
		return (0);
	if (history_parse_number(m, tok, n))
		return (1);
	return (0);
}

int	ft_history(t_minishell *m)
{
	t_list	*last;
	int		n;
	int		size;
	int		start;
	char	**tok;

	if (!m->history)
		return (0);
	last = lst_last(m->history);
	if (!last || !last->content)
		return (0);
	tok = ft_split((char *)last->content, ' ');
	if (parse_tokens(m, tok, &n))
		return (mem_free_array(&tok, "history"), m->last_status);
	mem_free_array(&tok, "history");
	if (n == 0)
		return (0);
	size = ft_lstsize(m->history);
	if (n < 0 || n >= size)
		start = 0;
	else
		start = size - n;
	print_history_from(m->history, start);
	return (0);
}
