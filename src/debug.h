/**
 * @file enhanced_debug.h
 * @brief Enhanced Debug Macros for C and C++ projects
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum LogLevel
 * @brief Log level enumeration
 */
typedef enum {
    LOG_TRACE, ///< Trace level
    LOG_DEBUG, ///< Debug level
    LOG_INFO,  ///< Informational level
    LOG_WARN,  ///< Warning level
    LOG_ERROR  ///< Error level
} LogLevel;

static LogLevel log_level = LOG_TRACE; ///< Default log level
static FILE *log_file = NULL;          ///< Log file pointer

/**
 * @def log_set_level(level)
 * @brief Set the log level
 * @param level Log level to be set
 */
#define log_set_level(level) (log_level = (level))

/**
 * @def log_set_file(file)
 * @brief Set the log file for output
 * @param file Path to the log file
 */
#define log_set_file(file) (log_file = fopen((file), "a"))

#define LOG_FMT "%s [%s] (%s:%d) "
#define LOG_ARGS(LOG_LVL) get_log_level_str(LOG_LVL), get_time_str(), __FILE__, __LINE__

const char *get_log_level_str(LogLevel level);
const char *get_time_str(void);

/**
 * @def log_log(level, ...)
 * @brief Log a message with a specified log level and format
 * @param level Log level
 * @param ... Message format and additional arguments
 */
#define log_log(level, ...) \
    do { \
        if (level >= log_level) { \
            if (log_file) { \
                fprintf(log_file, LOG_FMT, LOG_ARGS(level)); \
                fprintf(log_file, __VA_ARGS__); \
                fprintf(log_file, "\n"); \
                fflush(log_file); \
            } else { \
                fprintf(stderr, LOG_FMT, LOG_ARGS(level)); \
                fprintf(stderr, __VA_ARGS__); \
                fprintf(stderr, "\n"); \
            } \
        } \
    } while (0)

/**
 * @def log_trace(...)
 * @brief Log a trace message
 * @param ... Message format and additional arguments
 */
#define log_trace(...) log_log(LOG_TRACE, __VA_ARGS__)

/**
 * @def log_debug(...)
 * @brief Log a debug message
 * @param ... Message format and additional arguments
 */
#define log_debug(...) log_log(LOG_DEBUG, __VA_ARGS__)

/**
 * @def log_info(...)
 * @brief Log an informational message
 * @param ... Message format and additional arguments
 */
#define log_info(...) log_log(LOG_INFO, __VA_ARGS__)

/**
 * @def log_warn(...)
 * @brief Log a warning message
 * @param ... Message format and additional arguments
 */
#define log_warn(...) log_log(LOG_WARN, __VA_ARGS__)

/**
 * @def log_error(...)
 * @brief Log an error message
 * @param ... Message format and additional arguments
 */
#define log_error(...) log_log(LOG_ERROR, __VA_ARGS__)

/**
 * @def clean_errno()
 * @brief Get a string representation of the current errno value
 * @return A string representation of errno, or "None" if errno is 0
 */
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

/**
 * @def check(A, M, ...)
 * @brief Check a condition, log an error message and jump to the error label if the condition is false
 * @param A Condition to be checked
 * @param M Error message format
 * @param ... Additional arguments for the error message format
 */
#define check(A, M, ...) if (!(A)) { \
    log_error(M, ##__VA_ARGS__); errno = 0; goto error; }

/**
 * @def check_mem(A)
 * @brief Check for memory allocation, log an error message and jump to the error label if the allocation failed
 * @param A Pointer to the allocated memory
 */
#define check_mem(A) check((A), "Out of memory.")

/**
 * @def check_debug(A, M, ...)
 * @brief Check a condition, log a debug message and jump to the error label if the condition is false
 * @param A Condition to be checked
 * @param M Debug message format
 * @param ... Additional arguments for the debug message format
 */
#define check_debug(A, M, ...) if (!(A)) { log_debug(M, ##__VA_ARGS__); \
    errno = 0; goto error; }

/**
 * @brief Get log level string
 * @param level Log level
 * @return Log level string
 */
const char *get_log_level_str(LogLevel level) {
    static const char *level_str[] = {
        "TRACE",
        "DEBUG",
        "INFO",
        "WARN",
        "ERROR"
    };
    return level_str[level];
}

/**
 * @brief Get a formatted time string
 * @return Time string in the format "YYYY-MM-DD HH:MM:SS"
 */
const char *get_time_str(void) {
    static char time_str[20];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(time_str, sizeof(time_str) - 1, "%Y-%m-%d %H:%M:%S", t);
    return time_str;
}

#ifdef __cplusplus
}
#endif

#endif // __DEBUG_H__
