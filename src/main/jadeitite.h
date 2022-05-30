#ifndef JADEITITE_H
#define JADEITITE_H

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

//======================================
//             Logging
//======================================

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
void log_logTime(void) {
  char fmt[64];
  char buf[64];
  struct timeval tv;
  struct tm *tm;

  gettimeofday (&tv, NULL);
  tm = localtime (&tv.tv_sec);
  strftime (fmt, sizeof (fmt), "%H:%M:%S:%%06u", tm);
  snprintf (buf, sizeof (buf), fmt, tv.tv_usec);
  printf ("[%s]", buf);
}

void log_logSrc(const char *t_file, int t_line) {
  printf("[ %s:%d ]", t_file, t_line);
}

void log_logLevel(log_level t_level) {
  switch (t_level) {
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

void log_log(log_level t_level, const char *t_file, int t_line, const char *t_input, ...) {
  log_logTime();
  log_logSrc(t_file, t_line);
  log_logLevel(t_level);
  va_list l_argList;
  va_start(l_argList, t_input);
  vprintf(t_input, l_argList);
  va_end(l_argList);
  printf("\n");
}

#define GET_SRC_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_INFO(...) log_log(LOG_LEVEL_INFO, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_WARN(...) log_log(LOG_LEVEL_WARN, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_log(LOG_LEVEL_ERROR, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_log(LOG_LEVEL_FATAL, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) log_log(LOG_LEVEL_DEBUG, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)

//======================================
//             Structures
//======================================

#include <stdint.h>

/**
 * Callbacks structure contain all necessary callback for functional OpenGl.
 *
 * @struct onUpdate(void) - Called every frame. Used for drawing and other update event.
 * @struct onKeyboardDown(unsigned char, int, int) - Called on any key down.
 * @struct onKeyboardUp(unsigned char, int, int) - Called on any key up.
 * @struct onAttach(int, char **) - Called after initialized Amber framework and OpenGl.
 * @struct onDetach(int, char **) - Called on close/end.
 */
typedef struct {
  void (*onUpdate)(void);
  void (*onKeyboardDown)(unsigned char, int, int);
  void (*onKeyboardUp)(unsigned char, int, int);
  void (*onAttach)(void);
  void (*onDetach)(void);
  void (*onResize)(int, int);
} callbacks_t;

/**
 * Window properties structure contain all necessary variables for initialize window with OpenGl/Glut.
 *
 * @struct width - Window width/X.
 * @struct height - Window height/Y.
 * @struct label - Window name/label.
 * @struct autoRefresh - If is true then enable auto refreshing window
 */
typedef struct {
  int width;
  int height;
  const char *label;
  int autoRefresh;
} winProp_t;

typedef struct {
  uint8_t r, g, b;
} color_t;

//======================================
//           Entry point
//======================================

#define JADEITITE_VER_MAJOR 0
#define JADEITITE_VER_MINOR 1
#define JADEITITE_VER_PATCH 0

// Framework version date YYYYMMDD
#define JADEITITE_VER_DATE 20220530

/**
 * Function for setting up callbacks and window properties for APP.
 *
 * @param p_callbacks Callbacks function
 * @param p_winProp Windows properties
 * @param argc Argument count
 * @param argv Argument list
 *
 * @return Return error code, 0 as PASSED, otherwise as FAILED
 *
 * @see t_callbacks
 */
extern int setup(callbacks_t *p_callbacks, winProp_t *p_winProp, int argc, char *argv[]);

int main(int argc, char *argv[]) {
  LOG_INFO(
      "Jadeitite framework - [%d.%d.%d - %d]",
      JADEITITE_VER_MAJOR,
      JADEITITE_VER_MINOR,
      JADEITITE_VER_PATCH,
      JADEITITE_VER_DATE
  );

  callbacks_t l_callbacks;
  winProp_t l_windowProperties;

  int l_setup = setup(&l_callbacks, &l_windowProperties, argc, argv);



  LOG_INFO("Closing Jadeitite framework");
  return 0;
}


#endif //JADEITITE_H
