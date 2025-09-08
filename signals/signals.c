// Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
/* signals.c — version simple */
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

volatile sig_atomic_t	g_signal;

static void sigint_handler(int sig)
{
	(void)sig;
	g_signal |= SIG_FLAG;
	write(STDOUT_FILENO, "\n", 1);
	if(g_signal & RDL_FLAG)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*static*/ void sigquit_handler(int sig)
{
	(void)sig;

	debug_var("test\n");
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();


	//write(STDOUT_FILENO, "\r  \r", 40);
	//write(STDOUT_FILENO, "\n", 1);
	// write(STDOUT_FILENO, "\n", 1);
	///write(STDOUT_FILENO, PROMPT, ft_strlen(PROMPT));
}

void setup_signals(void)
{
	signal(SIGINT,  sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGQUIT, sigquit_handler); // TODO A VOIR
	// signal(SIGQUIT, NULL); // TODO A VOIR
}

void setup_signals_for_children(void)
{
	signal(SIGINT,  SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	//signal(SIGINT, sigquit_handler); // TODO A VOIR
	//signal(SIGQUIT, sigquit_handler); // TODO A VOIR
}


/* pas un sig
void handle_ctrl_d(char *line)
{
    if (!line)
    {
        write(STDOUT_FILENO, "exit\n", 5);
        exit(0);
    }
}*/