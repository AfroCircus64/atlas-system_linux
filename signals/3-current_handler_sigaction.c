#include "signals.h"

/**
 * current_handler_sigaction - retrieves current handler of the signal SIGINT
 *
 * Return: a pointer to the current handler of SIGINT or NULL
 */
void (*current_handler_sigaction(void))(int)
{
	struct sigaction sa;

	if (sigaction(SIGINT, NULL, &sa) == -1)
	{
		return (NULL);
	}
	return (sa.sa_handler);
}
