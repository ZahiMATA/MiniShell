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

static void	*readinput(t_minishell *m, char * prompt)
{
	int	test = 0;
	if (test)
		m->line = get_input();
	else
		m->line = readline(prompt);
	return (m->line);
}

char	*read_input(t_minishell *m, char * prompt)
{
	//if (ft_strcmp(prompt, PROMPT) == 0) // TODO A VOIR
	{
		g_signal |= RDL_FLAG;
		readinput(m, prompt);
		g_signal &= ~RDL_FLAG;
		if (m->line && *m->line)
			ft_add_history(m, m->line);
	}
	//else
	//	readinput(m, prompt);
	return m->line;
}
