#include <Python.h>
#include <stdio.h>

/**
 * print_python_list - prints some basic info about Python lists
 *
 * @p: python list object
 */
void print_python_list(PyObject *p)
{
	PyListObject *list = (PyListObject *)p;
	int size = Py_SIZE(list);

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %d\n", size);
	printf("[*] Allocated = %ld\n", list->allocated);

	for (int i = 0; i < size; i++)
	{
		PyObject *item = PyList_GetItem(p, i);

		printf("Element %d: %s\n", i, Py_TYPE(item)->tp_name);
	}
}
