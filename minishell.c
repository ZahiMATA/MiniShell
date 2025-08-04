#include "minishell.h"

int	minishell(char **env)
{
	t_minishell *m;
	char *line;

	exec_init_minishell(&m, env);
	while (1)
	{
		ft_putstr_fd("minishell$", STDOUT_FILENO);
		line = read_input(m, STDIN_FILENO);
		if (line == NULL)
			continue;
		//newline = strchr(line, '\n');
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		ft_putstr_fd("Texte entré : ", STDOUT_FILENO);
		ft_putstr(line);
		free(line);
	}

}

int	main(int argc, char *argv[], char *env[])
{
	(void) argv;
	if (argc == 1)
		minishell(env);
	else
		ft_putstr(ERROR_WRONGARGS);
}