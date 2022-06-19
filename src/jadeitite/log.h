#ifndef JADEITITE_LOG_H
#define JADEITITE_LOG_H

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

typedef enum {
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL,
  LOG_LEVEL_DEBUG
} log_level;

// src: https://stackoverflow.com/a/27678121
static void log_logTime(void) {
  char fmt[64];
  char buf[64];
  struct timeval tv;
  struct tm *tm;

  gettimeofday(&tv, NULL);
  tm = localtime(&tv.tv_sec);
  strftime(fmt, sizeof(fmt), "%H:%M:%S:%%06u", tm);
  snprintf(buf, sizeof(buf), fmt, tv.tv_usec);
  printf("[%s]", buf);
}

static void log_logSrc(const char *p_file, int p_line) {
  printf("[ %s:%d ]", p_file, p_line);
}

static void log_logLevel(log_level p_level) {
  switch (p_level) {
  case LOG_LEVEL_INFO:printf("[INFO]: ");
    break;
  case LOG_LEVEL_WARN:printf("[WARN]: ");
    break;
  case LOG_LEVEL_ERROR:printf("[ERROR]: ");
    break;
  case LOG_LEVEL_FATAL:printf("[FATAL]: ");
    break;
  case LOG_LEVEL_DEBUG:printf("[DEBUG]: ");
    break;
  default:printf("Undefined behaviour!\n");
    return;
  }
}

static void log_log(
  log_level p_level,
  const char *p_file,
  int p_line,
  const char *p_input,
  ...
) {
  log_logTime();
  log_logSrc(p_file, p_line);
  log_logLevel(p_level);
  va_list l_argList;
  va_start(l_argList, p_input);
  vprintf(p_input, l_argList);
  va_end(l_argList);
  printf("\n");
}

#define GET_SRC_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_INFO(...) log_log(LOG_LEVEL_INFO, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_WARN(...) log_log(LOG_LEVEL_WARN, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_log(LOG_LEVEL_ERROR, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_log(LOG_LEVEL_FATAL, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) log_log(LOG_LEVEL_DEBUG, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)

#endif //JADEITITE_LOG_H
