#include "minishell.h"

char	*read_input(t_minishell *m, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		n;
	//char	*line;
	char	*tmp;

	m->line = ft_strdup("");
	if (m->line == NULL)
		ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
	n = 1;
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
		{
			// pas besoin gere par le signal
			//if (errno == EINTR)
				//continue;
				//write(1, "n", 1);
			ft_return_perror(m, NULL, EXIT_FAILURE);
			return (NULL);
		}
		buffer[n] = '\0';
		tmp = m->line;
		m->line = ft_strjoin(m->line, buffer);
		free(tmp);
		if (m->line == NULL)
			ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		//m->last_status = EXIT_SUCCESS;
		if (ft_strchr(m->line, '\n'))
			return (m->line);
	}
	if (m->line[0] == '\0')
		return NULL;
	return m->line;
}
