#include "minishell.h"

char	*read_input(t_minishell *m, int got_signal)
{
	if (got_signal == GOT_NO_SIGNAL)
		m->line = readline(PROMPT);
	else
		m->line = readline("");
	if (m->line && *m->line)
	 	add_history(m->line);
	return m->line;
}
