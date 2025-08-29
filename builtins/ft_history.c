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

int	ft_history(t_minishell *m)
{
	t_list		*lst;
	int			i;

	lst = m->history;
	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		ft_putnbr_fd(i + 1, 1);
		write(1, "  ", 2);
		ft_putstr_fd(lst->content, 1);
		write(1, "\n", 1);
		i++;
		lst = lst -> next;
	}
	return (0);
}



/*
int	ft_history(char **argv)
{
	HIST_ENTRY	**lst;
	int			i;

	(void)argv;
	lst = history_list();
	if (!lst)
		return (0);
	i = 0;
	while (lst[i])
	{
		ft_putnbr_fd(i + 1, 1);
		write(1, "  ", 2);
		ft_putstr_fd(lst[i]->line, 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
	*/