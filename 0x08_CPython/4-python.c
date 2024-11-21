#include <Python.h>
#include <stdio.h>

/**
 * print_python_string - displays basic info about Python strings
 *
 * @p: Python object
 */
void print_python_string(PyObject *p)
{
	PyUnicodeObject *str_obj = NULL;
	const char *type_str = "";
	int kind;
	PyObject *utf8 = NULL;
	const char *utf8_cstr = NULL;

	if (!p || !PyUnicode_Check(p))
	{
		printf("[.] string object info\n");
		printf("  [ERROR] Invalid String Object\n");
		return;
	}

	str_obj = (PyUnicodeObject *)p;
	kind = PyUnicode_KIND(str_obj);

	switch (kind)
	{
		case PyUnicode_1BYTE_KIND:
			type_str = "compact ascii";
			break;
		case PyUnicode_2BYTE_KIND:
		case PyUnicode_4BYTE_KIND:
			type_str = "compact unicode object";
			break;
		default:
			type_str = "unknown";
			break;
	}

	printf("[.] string object info\n");
	printf("  type: %s\n", type_str);
	printf("  length: %ld\n", PyUnicode_GET_LENGTH(str_obj));

	utf8 = PyUnicode_AsUTF8String(p);
	if (utf8 == NULL)
	{
		PyErr_Print();
		return;
	}

	utf8_cstr = PyBytes_AS_STRING(utf8);
	printf("  value: %s\n", utf8_cstr);

	Py_DECREF(utf8);
}
