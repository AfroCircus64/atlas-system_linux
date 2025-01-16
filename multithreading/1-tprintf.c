#include "multithreading.h"

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

	pthread_t self = pthread_self();

	fprintf(stream, "[%lu]", (unsigned long)self);

	fputc(' ', stream);

	va_start(args, format);

	result = vfprintf(stream, format, args);

	va_end(args);

	return (result);
}
