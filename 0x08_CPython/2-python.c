#include <Python.h>
#include <stdio.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);

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

	length = PyList_Size(p);

	if (PyList_Check(p))
	{
		lst = (PyListObject *)p;
		capacity = lst->allocated;

		printf("[*] Python list info\n");
		printf("[*] Size of the Python List = %ld\n", length);
		printf("[*] Allocated = %ld\n", capacity);

		for (index = 0; index < length; index++)
		{
			element = lst->ob_item[index];
			typename = element->ob_type->tp_name;
			printf("Element %ld: %s\n", index, typename);
			if (PyBytes_Check(element))
				print_python_bytes(element);
		}
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
	total_size = PyBytes_Size(p);

	bytes_data = (PyBytesObject *)p;

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
	printf("  trying string: %s\n", PyBytes_AsString(p));
	printf("  first %ld bytes: ", display_size);
	for (byte_index = 0; byte_index < display_size; byte_index++)
	{
		printf("%02x", bytes_data->ob_sval[byte_index] & 0xff);
		if (byte_index != display_size - 1)
			printf(" ");
	}
	printf("\n");
}
