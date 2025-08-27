// Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
/* signals.c — version simple */
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void sigint_handler(int sig)
{
	(void)sig;
	g_signal = 1;
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, PROMPT, ft_strlen(PROMPT));
}

static void sigquit_handler(int sig)
{
    (void)sig;
}

void setup_signals(void)
{
	signal(SIGINT,  sigint_handler);
	signal(SIGQUIT, sigquit_handler);
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