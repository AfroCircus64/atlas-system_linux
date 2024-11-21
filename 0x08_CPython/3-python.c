#include <Python.h>
#include <stdio.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);
void print_python_float(PyObject *p);

/**
 * print_python_list - displays basic info about python lists
 *
 * @p: PyObject
 */
void print_python_list(PyObject *p)
{
	PyListObject *lst = NULL;
	PyObject *element = NULL;
	Py_ssize_t length, capacity, index;
	const char *typename;

	if (!p || !PyList_Check(p))
	{
		printf("[*] Python list info\n");
		printf("[ERROR] Invalid List Object\n");
		return;
	}

	lst = (PyListObject *)p;
	length = ((PyVarObject *)lst)->ob_size;
	capacity = lst->allocated;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", length);
	printf("[*] Allocated = %ld\n", capacity);

	for (index = 0; index < length; index++)
	{
		element = lst->ob_item[index];
		if (element == NULL)
		{
			printf("Element %ld: NULL\n", index);
			continue;
		}

		typename = element->ob_type->tp_name;
		printf("Element %ld: %s\n", index, typename);
		if (PyBytes_Check(element))
			print_python_bytes(element);
		if (PyFloat_Check(element))
			print_python_float(element);
	}
}

/**
 * print_python_bytes - displays basic info about Python bytes objects
 *
 * @p: Python object
 */
void print_python_bytes(PyObject *p)
{
	PyBytesObject *bytes_data = NULL;
	Py_ssize_t total_size, byte_index, display_size;

	if (!p || !PyBytes_Check(p))
	{
		printf("[.] bytes object info\n");
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	bytes_data = (PyBytesObject *)p;
	total_size = ((PyVarObject *)bytes_data)->ob_size;

	if (total_size >= 10)
	{
		display_size = 10;
	}
	else
	{
		display_size = total_size + 1;
	}

	printf("[.] bytes object info\n");
	printf("  size: %ld\n", total_size);
	printf("  trying string: %s\n", bytes_data->ob_sval);
	printf("  first %ld bytes: ", display_size);
	for (byte_index = 0; byte_index < display_size; byte_index++)
	{
		printf("%02x", bytes_data->ob_sval[byte_index] & 0xff);
		if (byte_index != display_size - 1)
			printf(" ");
	}
	printf("\n");
}

/**
 * print_python_float - displays basic info about Python float objects
 *
 * @p: Python object
 */
void print_python_float(PyObject *p)
{
	PyFloatObject *float_data = NULL;

	if (!p || !PyFloat_Check(p))
	{
		printf("[.] float object info\n");
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}

	float_data = (PyFloatObject *)p;

	double value = float_data->ob_fval;

	if (isinf(value))
	{
		printf("  value: inf\n");
	}
	else if (isnan(value))
	{
		printf("  value: nan\n");
	}
	else
	{
		if (fabs(value) > 1e+10 || fabs(value) < 1e-10)
		{
			printf("  value: %.15e\n", value);
		}
		else
		{
			printf("  value: %.15g\n", value);
		}
	}
}
