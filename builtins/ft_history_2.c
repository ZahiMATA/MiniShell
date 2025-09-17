/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:28:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/17 14:43:58 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

/* forward decls (implémentées dans ft_history_3.c) */
int		history_is_meta(const char *s);
void	history_usage(void);
int		history_scan_argc(char **tok);
int		history_check_flags(t_minishell *m, char **tok, int argc, int *n);

int	is_numeric(const char *s)
{
	size_t	i;

	if (!s || !*s)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

t_list	*lst_last(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	print_history_from(t_list *lst, int start_index)
{
	int	i;
	int	num;

	i = 0;
	num = 1;
	while (lst)
	{
		if (i >= start_index)
		{
			ft_putnbr_fd(num, 1);
			write(1, "  ", 2);
			ft_putstr_fd((char *)lst->content, 1);
			write(1, "\n", 1);
			num++;
		}
		i++;
		lst = lst->next;
	}
}

int	history_parse_validate(t_minishell *m, char **tok, int *argc, int *n)
{
	if (!tok || !tok[0] || ft_strcmp(tok[0], "history") != 0)
	{
		*n = -1;
		return (0);
	}
	*argc = history_scan_argc(tok);
	if (*argc == 1)
	{
		*n = -1;
		return (0);
	}
	if (history_check_flags(m, tok, *argc, n))
		return (1);
	return (0);
}

int	history_parse_number(t_minishell *m, char **tok, int *n)
{
	long long	ll;

	if (!is_numeric(tok[1]) || atoll_overflow(tok[1], &ll))
	{
		ft_putstr_fd("minishell: history: ", 2);
		ft_putstr_fd(tok[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		m->last_status = 2;
		return (1);
	}
	*n = (int)ll;
	return (0);
}
