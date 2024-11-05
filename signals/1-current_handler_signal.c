#include "signals.h"

/**
 * current_handler_signal - retrieves the current handler of the signal SIGINT
 *
 * Return: a pointer to the current handler of SIGINT or NULL
 */
void (*current_handler_signal(void))(int)
{
	void (*handler)(int) = signal(SIGINT, SIG_IGN);

	if (handler == SIG_ERR)
	{
		return (NULL);
	}

	signal(SIGINT, handler);

	return (handler);
}
