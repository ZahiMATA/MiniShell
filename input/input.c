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
