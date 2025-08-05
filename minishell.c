#include "minishell.h"

int	minishell(char **env)
{
	t_minishell *m;
	char *line;

	m = NULL;
	(void)env;
	while (1)
	{
		exec_init_minishell(&m);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		line = read_input(m, STDIN_FILENO);
		if (line == NULL)
			continue;
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		// lex
		// parse qui renvoie la liste des cmds
		// exec_feed_pipex(...); ou buildin ou redirection
		ft_putstr_fd("Texte entré : ", STDOUT_FILENO);
		ft_putstr_fd(line, STDERR_FILENO);
		free(line);
		debug_show_args(m);
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