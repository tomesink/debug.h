# debug.h
Log and debugging macros for C and C++

This header-only library provides a set of enhanced debug macros for C and C++ projects, including log levels, log file support, and better message formatting. It can help you quickly and easily add logging functionality to your project, without the need for a more complex logging library.

## Features

- Log levels: Trace, Debug, Info, Warn, and Error
- Customizable log level
- Memory checks
- Optional log file output
- Compatible with both C and C++ projects
- Detailed comments in Doxygen format for automatic documentation generation

## Usage

1. Include the `enhanced_debug.h` header file in your project.
2. Set the desired log level using the `log_set_level()` macro.
3. Optionally, set a log file for output using the `log_set_file()` macro.
4. Use the `log_trace()`, `log_debug()`, `log_info()`, `log_warn()`, and `log_error()` macros to log messages with different log levels.

## Log Example

```c
#include "debug.h"

int main() {
    // Set log level to INFO
    log_set_level(LOG_INFO);

    // Optionally, set a log file for output
    log_set_file("log.txt");

    // Log messages with different log levels
    log_trace("This is a trace message");
    log_debug("This is a debug message");
    log_info("This is an informational message");
    log_warn("This is a warning message");
    log_error("This is an error message");

    return 0;
}
```

## Memory Check Macros Examples

The following examples demonstrate how to use the memory check macros provided by the Enhanced Debug Macros library.

#### Example 1: Using `check`

```c
#include "debug.h"

int example_function(int value) {
    // Check if the value is greater than zero
    check(value > 0, "Value must be greater than zero, got: %d", value);

    // Perform other operations
    // ...

    return 0;

error:
    // Error handling
    return -1;
}

int main() {
    log_set_level(LOG_ERROR);
    int result = example_function(-1);
    if (result < 0) {
        log_error("An error occurred in example_function");
    }
}


```

#### Example 2: Using `check_mem`

```c
#include "debug.h"
#include <stdlib.h>

int memory_allocation_example() {
    int *buffer = (int *)malloc(1024 * sizeof(int));

    // Check if the memory allocation was successful
    check_mem(buffer);

    // Perform other operations
    // ...

    free(buffer);
    return 0;

error:
    // Error handling
    return -1;
}

int main() {
    log_set_level(LOG_ERROR);
    int result = memory_allocation_example();
    if (result < 0) {
        log_error("An error occurred in memory_allocation_example");
    }
}
```

#### Example 3: Using `check_debug`

```c
#include "debug.h"

int debug_check_example(int value) {
    // Check if the value is greater than zero, log a debug message if not
    check_debug(value > 0, "Value must be greater than zero, got: %d", value);

    // Perform other operations
    // ...

    return 0;

error:
    // Error handling
    return -1;
}

int main() {
    log_set_level(LOG_DEBUG);
    int result = debug_check_example(-1);
    if (result < 0) {
        log_error("An error occurred in debug_check_example");
    }
}

```

# References

These macros are heavily inspired by:
- [log.c](https://github.com/rxi/log.c) library 
- [Learn C The Hard Way](https://amzn.to/40mUMR5) book by Zed Shaw (the mem check macros are reused)
