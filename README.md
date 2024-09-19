# Baseutil
A library containing basic utilities that I personally find useful in C.
The library is not portable. It uses GNU17 standard and POSIX.1-2008.

`dbg.h` provides macros useful in logging, debugging and error handling.

`macros.h` provides many commonly used macros.

`test_macros.h` specifically provides macros for use with the unit testing framework Check.
Usage examples are available in the `test` directory.

`utilities.h` provides common utility functions related to basic primitive types.
It also provides function type definitions that may be used for generic data structures.

### Macros and compilation flags

The following macros may be defined to tweak the library:

- `SILENT` disables logging and asserts.
- `NDEBUG` disables asserts.
- `CURRENT_FILE` is used to print the filename in dbg macros. It uses `__FILE__` by default,
but this may be changed to suit your needs. The library provides `FILENAME`, which only prints the name of the file.
- `STACKTRACE_CALLS` sets the maximum number of function calls displayed in the stacktrace in most macros.

To provide meaningful function names, you may have to add `-rdynamic` to gcc's linker options.

When building with CMake, you may exclude `test_macros.h` and other features that rely on Check by setting `USE_CHECK` to OFF.