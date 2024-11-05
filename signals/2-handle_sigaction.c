#include "signals.h"

/**
 * sigint_handler - function to print Gotcha! every time Control-C is pressed
 *
 * @signum: signal number
 */
void sigint_handler(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}

/**
 * handle_sigaction - function that set a handler for the signal SIGINT
 *
 * Return: Success (0) or Error (-1)
 */
int handle_sigaction(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));

	sa.sa_handler = sigint_handler;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (-1);
	}
	return (0);
}
