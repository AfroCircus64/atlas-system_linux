#include "signals.h"

/**
 * sigint_handler - function to print Gotcha! every time Control-C is pressed
 *
 * @signum: signal number
 */
void sigint_handler(int signum)
{
	printf("Gotcha! [%d]\n", signum);
}

/**
 * handle_signal - function that set a handler for the signal SIGINT
 *
 * Return: Success (0) or Error (-1)
 */
int handle_signal(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		return (-1);
	}
	return (0);
}
