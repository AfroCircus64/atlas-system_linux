#include "multithreading.h"

/**
 * thread_entry - entry point
 *
 * @arg: argument
 *
 * Return: NULL
 */
void *thread_entry(void *arg)
{
	printf("%s\n", (char *)arg);
	pthread_exit(NULL);
}
