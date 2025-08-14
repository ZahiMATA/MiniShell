#include "minishell.h"

char	*read_input(t_minishell *m, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		n;
	char	*line;
	char	*tmp;

	line = ft_strdup("");
	if (line == NULL)
		ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
	n = 1;
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
		{
			ft_return_perror(m, NULL, EXIT_FAILURE);
			return (NULL);
		}
		buffer[n] = '\0';
		tmp = line;
		line = ft_strjoin(line, buffer);
		free(tmp);
		if (line == NULL)
			ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		m->last_status = EXIT_SUCCESS;
		if (ft_strchr(line, '\n'))
			return (line);
	}
	if (*line == '\0')
	{
		free(line);
		ft_exit_with_status(m, EXIT, EXIT_SUCCESS);
	}
	return line;
}