#include "minishell.h"
#include <limits.h> /* pour unsigned char cast */

int	ft_is_numeric(char *str) // OK à mettre en libft
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_minishell *m, t_cmd *cmd)
{
	int	status;

	if (!cmd || !cmd->args || !cmd->args[1])
	{
		ft_printf_fd(STDOUT_FILENO, "exit\n");
		status = (unsigned char)m->last_status;
		mem_free_all(m);
		exit(status); /* exit avec dernier status */
	}
	if (cmd->args[2]) /* trop d’arguments */
	{
		ft_printf_fd(STDERR_FILENO, "%s: exit: too many arguments\n", MINISHELL);
		return (1);
	}
	if (!ft_is_numeric(cmd->args[1]))
	{
		ft_printf_fd(STDERR_FILENO, "%s: exit: %s: numeric argument required\n",
			MINISHELL, cmd->args[1]);
		ft_printf_fd(STDOUT_FILENO, "exit\n");
		mem_free_all(m);
		exit(255);
	}
	status = (int)(unsigned char)ft_atoi(cmd->args[1]);
	ft_printf_fd(STDOUT_FILENO, "exit\n");
	mem_free_all(m);
	exit(status);
}
