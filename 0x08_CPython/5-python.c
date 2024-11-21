#include <Python.h>
#include <stdio.h>

/**
 * print_python_int - displays basic info about Python integers
 *
 * @p: Python object
 */
void print_python_int(PyObject *p)
{
	if (!PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}

	PyLongObject *long_obj = (PyLongObject *)p;
	Py_ssize_t size = long_obj->ob_base.ob_size;
	digit *digits = long_obj->ob_digit;

	if (size == 0)
	{
		printf("0\n");
		return;
	}

	Py_ssize_t max_digits = (sizeof(unsigned long) * 8) / PyLong_SHIFT;

	if (size > max_digits || (size == max_digits && digits[size - 1] != 0))
	{
		printf("C unsigned long int overflow\n");
		return;
	}

	unsigned long result = 0;
	Py_ssize_t abs_size = size < 0 ? -size : size;

	for (Py_ssize_t i = 0; i < abs_size; i++)
	{
		result = (result << PyLong_SHIFT) | digits[i];
	}

	if (size < 0)
		printf("-");
	printf("%lu\n", result);
}
