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



char	*get_input(void)
{
	char	*line;

	if (isatty(STDIN_FILENO))
	{
		//debug_var("1");
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
	}
	else
	{
		//debug_var("2");
		line = get_next_line(STDIN_FILENO);
		if (line && *line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
	}
	return (line);
}

char	*read_line(t_minishell *m, char *prompt)
{
	char	buffer[BUFFER_SIZE + 1];
	int		n;

	ft_printf_fd(STDOUT_FILENO, "%s", prompt);
	m->line = NULL;
	n = 1;
	while (n > 0)
	{
		n = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (n < 0)
		{
			//ft_return_perror(m, NULL, EXIT_FAILURE);
			m->status_heredoc = EXIT_1;
			return (NULL);
		}
		buffer[n] = '\0';
		m->line = ft_strjoin_2(&m->line, buffer);
		if (m->line == NULL)
			ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		if (ft_strchr(m->line, '\n'))
			return (m->line);
	}
	if (m->line[0] == '\0')
		return NULL;
	return m->line;
}

static void	*readinput(t_minishell *m, char * prompt)
{
	if (DEBUG_TEST)
		m->line = get_input();
	else if (ft_strcmp(prompt, PROMPT) == 0)
		m->line = readline(prompt);
	else
	{
		//printf("%s", prompt);
		m->line = read_line(m, prompt);
		if (m->line && *m->line && m->line[ft_strlen(m->line) - 1] == '\n')
		 	m->line[ft_strlen(m->line) - 1] = '\0';
	}
	return (m->line);
}

char	*read_input(t_minishell *m, char * prompt)
{
	if (ft_strcmp(prompt, PROMPT) == 0)
	{
		g_signal |= RDL_FLAG;
		readinput(m, prompt);
		g_signal &= ~RDL_FLAG;
		if (m->line && *m->line)
			ft_add_history(m, m->line);
	}
	else
	 	readinput(m, prompt);
	return m->line;
}
