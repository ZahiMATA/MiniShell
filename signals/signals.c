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
	if (g_signal & RDL_FLAG)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
#include <sys/ioctl.h>
static void sigint_handler_hd(int sig)
{
	(void)sig;
	g_signal |= SIG_FLAG;

	write(STDOUT_FILENO, "\n", 1);
	int i = g_signal + '0';
	write(1, &i, 1);

	rl_done = 1;
	//write(STDOUT_FILENO, "\n", 1);
	ioctl(STDOUT_FILENO, TIOCSTI, "\n");
	        ioctl(STDOUT_FILENO, TIOCSTI, "\n");
        rl_on_new_line();
        rl_replace_line("", 0);
	//write(STDOUT_FILENO, "\n", 1);
	//if (g_signal & HEREDOC_FLAG)
	/*{
		//rl_replace_line("", 0);
		ioctl(STDOUT_FILENO, TIOCSTI, "\n");

		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}*/
        /*rl_done = 1;
        ioctl(STDOUT_FILENO, TIOCSTI, "\n");
        g_signal = SIGINT;
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();*/

	//rl_done = 1;
}

/*static* / void sigquit_handler(int sig)
{
	(void)sig;

	debug_var("test\n");
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}*/

void setup_signals(void)
{
	signal(SIGINT,  sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void setup_signals_for_children(void)
{
	signal(SIGINT,  SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void setup_signals_for_heredoc(void)
{
	signal(SIGINT,  sigint_handler_hd);
	signal(SIGQUIT, SIG_IGN);
}
