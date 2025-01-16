#include "multithreading.h"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

/**
 * init_mutex - initializes the mutex
 *
 * Return: Nothing
 */
__attribute__((constructor))
static void init_mutex(void)
{
	pthread_mutex_init(&mtx, NULL);
}

/**
 * destroy_mutex - destroys the mutex
 *
 * Return: Nothing
 */
__attribute__((destructor))
static void destroy_mutex(void)
{
	pthread_mutex_destroy(&mtx);
}


/**
 * tprintf - prints a formatted string
 *
 * @format: string
 *
 * Return: result
 */
int tprintf(const char *format, ...)
{
	va_list args;
	int result;
	FILE *stream = stdout;

	pthread_mutex_lock(&mtx);

	pthread_t self = pthread_self();

	fprintf(stream, "[%lu]", (unsigned long)self);
	fputc(' ', stream);

	va_start(args, format);
	result = vfprintf(stream, format, args);
	va_end(args);

	pthread_mutex_unlock(&mtx);

	return (result);
}
