char	*read_input(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		n;
	char	*line;
	char	*tmp;

	line = ft_strdup("");
	if (line == NULL)
	{
		ft_minishell_error();
		return (NULL);
	}
	n = 1;
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
		{
			ft_minishell_error();
			return (NULL);			
		}
		else if (n == 0)
		{
			if (*line == 0)
			{
				free(line);
				ft_exit();
			}
			break;
		}
		buffer[n] = '\0';
		tmp = line;
		line = ft_strjoin(line, buffer);
		if (line == NULL)
		{
			ft_minishell_error();
			free(tmp);
			return (NULL);
		}
		free(tmp);
		if (ft_strchr(line, '\n'))
			return (line);
	}
	return line;
}