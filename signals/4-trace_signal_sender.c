#include "signals.h"

/**
 * sigquit_handler - quit handler
 *
 * @signo: signal number
 * @info: pointer to an info struct
 * @context: pointer to a context struct
 */
void sigquit_handler(int signo, siginfo_t *info, void *context)
{
	(void)context;

	if (signo == SIGQUIT)
	{
		printf("SIGQUIT sent by %d\n", info->si_pid);
	}
}

/**
 * trace_signal_sender - defines a handler for the signal SIGQUIT
 *
 * Return: Success (0) or Error (-1)
 */
int trace_signal_sender(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = sigquit_handler;
	sa.sa_flags = SA_SIGINFO;

	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (-1);
	}
	return (0);
}
