#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "signals.h"

/**
 * print_hello - Prints hello when a signal is caught
 * @signum: Signal no
 */
void print_hello(int signum)
{
	(void)signum;
	printf("Hello :)\n");
	fflush(stdout);
}

/**
 * set_print_hello - Set 'print_hello' as the handler for SIGINT
 */
void set_print_hello(void)
{
	signal(SIGINT, print_hello);
}
