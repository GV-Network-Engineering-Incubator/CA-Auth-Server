#ifndef __LOGGER_H
#define __LOGGER_H

/* Log Levels */
#define LL_DEBUG 0
#define LL_VERBOSE 1
#define LL_NOTICE 2
#define LL_WARNING 3
#define CONFIG_DEFAULT_VERBOSITY LL_NOTICE

/* Log Config Settings */
#define LOG_MAX_LEN 1024

#ifdef __GNUC__ /* Compiler optimizations */
void serverLog(int level, const char* message, ...)
  __attribute__((format(printf, 2, 3)));
#else
void serverLog(int level, const char* message, ...);
#endif


#endif
