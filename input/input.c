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
	// rl_replace_line(PROMPT, 0);
	// rl_on_new_line();
	// rl_redisplay();
	//m->line = readline(PROMPT);
	if (got_signal == GOT_NO_SIGNAL)
		m->line = readline(PROMPT);
	 else
	 	m->line = readline("\033[C\b");
//	 	m->line = readline("\033[D\033[C");
	if (m->line && *m->line)
	 	add_history(m->line);

	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();

	return m->line;
}
