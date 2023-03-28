#include "/Library/Frameworks/Python.framework/Versions/3.11/Headers/Python.h"
#define PY_SSIZE_T_CLEAN

/// @brief 
/// @return 

int stats()
{
    char const *argv[];
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL)
    {
        fprintf(stderr, "Fatal Error: Cannot decode arg[0]\n");
        exit(1);
    }

    Py_SetProgramName(program);
    Py_Initialize();

    PyRun_SimpleString("exec(open('stats.py').read())");

    // Finish the Python Interpreter
    if(Py_FinalizeEx() < 0){
        exit(120);
    }

    PyMem_RawFree(program);

    return 0;
}