#include "minishell.h"
#include <limits.h>

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

static int	is_numeric(const char *s)
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

static t_list	*lst_last(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	print_history_from(t_list *lst, int start_index)
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

static char	**split_space(const char *s)
{
	return (ft_split(s, ' '));
}

static void	free_split(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	print_history_usage(void)
{
	ft_putstr_fd(
		"history: usage: history [-c] [-d offset] [n] or history -anrw [filename] or history -ps arg [arg...]\n",
		2);
}

static int	atoll_overflow(const char *s, long long *out)
{
	size_t				i;
	int					sign;
	unsigned long long	acc;
	unsigned long long	limit;
	unsigned int		d;

	i = 0;
	sign = 1;
	acc = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (sign == 1)
		limit = (unsigned long long)LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MAX + 1ULL;
	while (s[i] != '\0')
	{
		d = (unsigned int)(s[i] - '0');
		if (acc > (limit / 10))
			return (1);
		if (acc == (limit / 10) && d > (unsigned int)(limit % 10))
			return (1);
		acc = acc * 10 + d;
		i++;
	}
	if (out != NULL)
	{
		if (sign == 1)
			*out = (long long)acc;
		else
			*out = -(long long)acc;
	}
	return (0);
}
static int	is_meta(const char *s)
{
	if (!s)
		return (0);
	if (ft_strcmp(s, "|") == 0)
		return (1);
	if (ft_strcmp(s, "<") == 0)
		return (1);
	if (ft_strcmp(s, ">") == 0)
		return (1);
	if (ft_strcmp(s, "<<") == 0)
		return (1);
	if (ft_strcmp(s, ">>") == 0)
		return (1);
	return (0);
}

static int	parse_tokens(t_minishell *m, char **tok, int *n)
{
	long long	ll;
	int			i;
	int			argc;

	if (!tok || !tok[0] || ft_strcmp(tok[0], "history") != 0)
	{
		*n = -1;
		return (0);
	}

	i = 1;
	while (tok[i] && !is_meta(tok[i]))
		i++;
	argc = i;

	if (argc == 1)
	{
		*n = -1;
		return (0);
	}

	if (tok[1][0] == '-' && tok[1][1] != '\0')
	{
		ft_putstr_fd("minishell: history: ", 2);
		ft_putstr_fd(tok[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		print_history_usage();
		m->last_status = 2;
		return (1);
	}

	if (argc > 2)
	{
		ft_putstr_fd("minishell: history: too many arguments\n", 2);
		m->last_status = 2;
		return (1);
	}

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


int	ft_history(t_minishell *m)
{
	t_list		*last;
	int			n;
	int			size;
	int			start;
	char		**tok;

	if (!m->history)
		return (0);
	last = lst_last(m->history);
	if (!last || !last->content)
		return (0);
	tok = split_space((char *)last->content);
	if (parse_tokens(m, tok, &n))
		return (free_split(tok), m->last_status);
	free_split(tok);
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
