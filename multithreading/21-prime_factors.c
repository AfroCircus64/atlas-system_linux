#include "multithreading.h"

/**
 * prime_factors - finds prime factors
 *
 * @s: string
 *
 * Return: factors
 */
list_t *prime_factors(char const *s)
{
	list_t *factors = malloc(sizeof(list_t));

	if (!factors)
	{
		return (NULL);
	}

	list_init(factors);

	unsigned long n = strtoul(s, NULL, 10);
	unsigned long i;

	for (i = 2; i * i <= n; i++)
	{
		while (n % i == 0)
		{
			unsigned long *factor = malloc(sizeof(unsigned long));

			if (!factor)
			{
				list_destroy(factors, free);
				free(factors);
				return (NULL);
			}

			*factor = i;
			list_add(factors, factor);
			n /= i;
		}
	}

	if (n > 1)
	{
		unsigned long *factor = malloc(sizeof(unsigned long));

		if (!factor)
		{
			list_destroy(factors, free);
			free(factors);
			return (NULL);
		}

		*factor = n;
		list_add(factors, factor);
	}

	return (factors);
}
