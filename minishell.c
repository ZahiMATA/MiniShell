int	minishell()
{
	char *line;
	
	while (1)
	{
		ft_putstr_fd("minishell$", STDOUT_FILENO)
		line = read_input(STDIN_FILENO);
		if (line == NULL)
			continue;
		newline = strchr(line, '\n');
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		ft_putstr_fd("Texte entré : ", STDOUT_FILENO);
		ft_putstr(line, STDOUT_FILENO);
		free(line);
	}
	
}

int	main(int argc, char *argv)
(
	minishell();
)