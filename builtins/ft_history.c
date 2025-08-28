#include "minishell.h"

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