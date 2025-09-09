#include "minishell.h"

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

static int	parse_tokens(t_minishell *m, char **tok, int *n)
{
	if (!tok || !tok[0] || ft_strcmp(tok[0], "history") != 0)
	{
		*n = -1;
		return (0);
	}
	if (tok[1] == NULL)
	{
		*n = -1;
		return (0);
	}
	if (tok[2] != NULL)
	{
		ft_putstr_fd("minishell: history: too many arguments\n", 2);
		m->last_status = 2;
		return (1);
	}
	if (!is_numeric(tok[1]))
	{
		ft_putstr_fd("minishell: history: ", 2);
		ft_putstr_fd(tok[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		m->last_status = 2;
		return (1);
	}
	*n = ft_atoi(tok[1]);
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
