#include "signals.h"

/**
 * sigint_handler - prints the status of the signal
 *
 * @signum: signal number
 */
void sigint_handler(int signum)
{
	printf("Caught %d\n", signum);
	printf("Signal recieved\n");
	_exit(EXIT_SUCCESS);
}

/**
 * main - sets a handler for the signal SIGINT
 *
 * Return: success
 */
int main(void)
{
	struct sigaction sa;

	sa.sa_handler = &sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESETHAND;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (EXIT_FAILURE);
	}
	pause();

	return (EXIT_SUCCESS);
}
