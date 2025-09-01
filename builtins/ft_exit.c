#include "minishell.h"

int	ft_is_numeric(char *str) //TODO a mettre dans libft
{
	int	i;

	if (!str || !str[0])
		return (0);

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;

	if (!str[i]) // juste un + ou - seul
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
	int status;

	ft_printf_fd(STDOUT_FILENO, "exit\n");
	if(cmd == NULL || cmd->args == NULL || cmd->args[1] == NULL)
	{
		mem_free_all(m);
		exit(0);
	}
	if (!ft_is_numeric(cmd->args[1]))
	{
		ft_printf_fd(STDERR_FILENO, "exit: numeric argument required\n");
		exit(255);
	}
	else if (cmd->args[2])
	{
		ft_printf_fd(STDERR_FILENO, "%s: exit: too many arguments\n", MINISHELL);
		return(1);
	}
	status = ft_atoi(cmd->args[1]) % 256;
	mem_free_all(m);
	exit(status);

/*
    write(1, "exit\n", 5);
    if(!argv[1])
        exit(0);
    if (!ft_is_numeric(argv[1]))
    {
        write(2, "exit: numeric argument required\n", 32);
        exit(255);
    }
    else if (argv[2])
    {
        write(2, "exit: too many arguments\n", 26);
        return(1);
    }
    exit(ft_atoi(argv[1]) % 256); // modUlo car peux afficher que 8bit
*/
}
