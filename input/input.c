/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:42:17 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/27 15:42:17 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char	*read_input(t_minishell *m, int got_signal)
{
	(void)got_signal;
	g_signal |= RDL_FLAG;
	m->line = readline(PROMPT);
	g_signal &= ~RDL_FLAG;
	if (m->line && *m->line)
		ft_add_history(m, m->line);
	return m->line;
}

#include "minishell.h"
char	*read_line(t_minishell *m, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int	n;
	//char    *line;
	//char    *tmp;

	m->line = NULL;
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
		m->line = ft_strjoin_2(&m->line, buffer);
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
