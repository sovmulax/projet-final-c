#include <Python.h>

int main(int argc, char *argv[]) {
    PyObject *pName, *pModule, *pFunc, *pResult;
    int arg;

    // Initialize Python Interpreter
    Py_Initialize();

    // Load the module object
    pName = PyUnicode_FromString("mymodule");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    // Check if the module was loaded
    if (pModule == NULL) {
        printf("Failed to load mymodule\n");
        return 1;
    }

    // Load the function object
    pFunc = PyObject_GetAttrString(pModule, "myfunction");

    // Check if the function was loaded
    if (!PyCallable_Check(pFunc)) {
        printf("myfunction not found or not callable\n");
        return 1;
    }

    // Call the function with one argument
    arg = 42;
    pResult = PyObject_CallFunction(pFunc, "i", arg);

    // Check if the function call was successful
    if (pResult == NULL) {
        printf("Function call failed\n");
        return 1;
    }

    // Get the result from the function call
    int result = PyLong_AsLong(pResult);
    printf("Result: %d\n", result);

    // Cleanup
    Py_DECREF(pFunc);
    Py_DECREF(pModule);
    Py_DECREF(pResult);

    // Shutdown Python Interpreter
    Py_Finalize();

    return 0;
}
