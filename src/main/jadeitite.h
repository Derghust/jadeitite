#ifndef JADEITITE_H
#define JADEITITE_H

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include <GL/freeglut.h>

//======================================
//             Logging
//======================================

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

  gettimeofday(&tv, NULL);
  tm = localtime(&tv.tv_sec);
  strftime(fmt, sizeof(fmt), "%H:%M:%S:%%06u", tm);
  snprintf(buf, sizeof(buf), fmt, tv.tv_usec);
  printf("[%s]", buf);
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
 * Used for setting up callback for Jadeitite framework
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
  void (*onAttach)(int, char**);
  void (*onDetach)(int, char**);
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

// Vectors

typedef struct {
  uint8_t x, y;
} vec_2_u8;

typedef struct {
  uint16_t x, y;
} vec_2_u16;

typedef struct {
  uint32_t x, y;
} vec_2_u32;

typedef struct {
  uint8_t x, y, z;
} vec_3_u8;

typedef struct {
  uint16_t x, y, z;
} vec_3_u16;

typedef struct {
  uint32_t x, y, z;
} vec_3_u32;

typedef struct {
  int8_t x, y;
} vec_2_s8;

typedef struct {
  int16_t x, y;
} vec_2_s16;

typedef struct {
  int32_t x, y;
} vec_2_s32;

typedef struct {
  int8_t x, y, z;
} vec_3_s8;

typedef struct {
  int16_t x, y, z;
} vec_3_s16;

typedef struct {
  int32_t x, y, z;
} vec_3_s32;

//======================================
//            Constants
//======================================

static const float s_jadeitite_pi = 3.14159f;

//======================================
//              Utils
//======================================

// https://www.strudel.org.uk/itoa/
char *citoa(int val, int base) {
  if (val == 0) {
    return "0";
  } else {
    static char buf[32] = {0};
    int i = 30;
    for (; val && i; --i, val /= base)
      buf[i] = "0123456789abcdef"[val % base];
    return &buf[i + 1];
  }
}

//======================================
//          Glut engine/run
//======================================

/**
 * Window run will call app callbacks.
 *
 * @param t_callbacks App callbacks (onUpdate, onKeyboardDown, onKeyboardUp, onAttach, onDetach).
 * @param t_winProp Window properties.
 */
static void window_run(callbacks_t *t_callbacks, winProp_t *t_winProp) {
  glutDisplayFunc(t_callbacks->onUpdate);
  if (t_winProp->autoRefresh) {
    glutIdleFunc(t_callbacks->onUpdate);
  } else {
    glutIgnoreKeyRepeat(1);
  }
//  glutReshapeFunc(t_callbacks->onResize);
  glutKeyboardFunc(t_callbacks->onKeyboardDown);
  glutKeyboardUpFunc(t_callbacks->onKeyboardUp);
  glutMainLoop();
}

//======================================
//          OpenGl core
//======================================

static inline void render_color(GLubyte r, GLubyte g, GLubyte b) {
  glColor3ub(r, g, b);
}

/**
 * Set color for clear
 *
 * @param r Red as byte [0-255]
 * @param g Green as byte [0-255]
 * @param b Blue as byte [0-255]
 */
static inline void render_set_clear_color(GLclampf r, GLclampf g, GLclampf b) {
  glClearColor(r, g, b, 1.0f);
}

/**
 * Clear window
 */
static inline void render_begin(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Swap render buffer
 */
static inline void render_end(void) {
  glutSwapBuffers();
}

/**
 * In case if we will have problem with rendering/drawing corner with primitive drawing lines,
 * then use this function onAttach.
 */
static inline void render_fix_corner(void) {
  glTranslatef(0.5f, 0.5f, 0);
}

//======================================
//          OpenGl window
//======================================

static winProp_t g_jadeitite_windowProperties;
static uint8_t g_jadeitite_pixel_size = 1;

void window_init(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(g_jadeitite_windowProperties.width, g_jadeitite_windowProperties.height);
  glutCreateWindow(g_jadeitite_windowProperties.label);
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
                GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}

void window_resize(int width, int height) {
  glutReshapeWindow(g_jadeitite_windowProperties.width, g_jadeitite_windowProperties.height);
}

//======================================
//      OpenGl core rendering
//======================================

uint8_t renderer_get_pixelSize(void) {
  return g_jadeitite_pixel_size;
}

void renderer_set_pixelSize(uint8_t t_value) {
  g_jadeitite_pixel_size = t_value;
}

void render_set_projection_2DOrthographic() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, g_jadeitite_windowProperties.width, g_jadeitite_windowProperties.height, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/**
 * Set OpenGl projection to 3D perspective.
 *
 * @param width Usually set to window width/X.
 * @param height Usually se to window height/Y.
 * @param fov Set field of view.
 * @param zNear Set minimum render distance from view point.
 * @param zFar Set maximum render distance from view point.
 */
void render_set_projection_3DPerspective(
    GLdouble width,
    GLdouble height,
    GLdouble fov,
    GLdouble zNear,
    GLdouble zFar
) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov, width / height, zNear, zFar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

//======================================
//          OpenGl drawing
//======================================

/**
 * Draw point/pixel on window with integer position.
 *
 * @param t_posX Position X in window as Integer.
 * @param t_posY Position Y in window as Integer.
 */
static void draw_point_int(GLint t_posX, GLint t_posY) {
  if (g_jadeitite_pixel_size == 1) {
    glBegin(GL_POINTS);
    glVertex2i(t_posX, t_posY);
    glEnd();
  } else {
    const GLint l_startX = t_posX * g_jadeitite_pixel_size;
    const GLint l_startY = t_posY * g_jadeitite_pixel_size;
    const GLint l_endX = l_startX + g_jadeitite_pixel_size;
    const GLint l_endY = l_startY + g_jadeitite_pixel_size;

    glBegin(GL_QUADS);
    glVertex2i(l_startX, l_startY);
    glVertex2i(l_endX, l_startY);
    glVertex2i(l_endX, l_endY);
    glVertex2i(l_startX, l_endY);

    glEnd();
  }
}

/**
 * Draw point/pixel on window with integer position fast (without resizer).
 *
 * @param t_posX Position X in window as Integer.
 * @param t_posY Position Y in window as Integer.
 */
static void draw_point_fast_int(GLint t_posX, GLint t_posY) {
  glBegin(GL_POINTS);
  glVertex2i(t_posX, t_posY);
  glEnd();
}

/**
 * Draw point/pixel on window with float position.
 *
 * @param t_posX Position X in window as Float.
 * @param t_posY Position Y in window as Float.
 */
static void draw_point_float(GLfloat t_posX, GLfloat t_posY) {
  glBegin(GL_POINTS);
  glVertex2f(t_posX, t_posY);
  glEnd();
}

/**
 * Draw point/pixel on window with double position.
 *
 * @param t_posX Position X in window as Double.
 * @param t_posY Position Y in window as Double.
 */
static void draw_point_double(GLdouble t_posX, GLdouble t_posY) {
  glBegin(GL_POINTS);
  glVertex2d(t_posX, t_posY);
  glEnd();
}

/**
 * Draw multiple point/pixel on window with integer position.
 *
 * @param t_posX Pointer of positions X in window as Integer.
 * @param t_posY Pointer of positions Y in window as Integer.
 * @param t_count Count of positions/points.
 *
 * @warning Be aware of pointers and count, there are no checking and can crash on overflow!
 */
static void draw_points_int(GLint *t_posX, GLint *t_posY, size_t t_count) {
  glBegin(GL_POINTS);
  for (size_t i = 0; i < t_count; ++i) {
    glVertex2i(t_posX[i], t_posY[i]);
  }
  glEnd();
}

/**
 * Draw multiple point/pixel on window with float position.
 *
 * @param t_posX Pointer of positions X in window as Float.
 * @param t_posY Pointer of positions Y in window as Float.
 * @param t_count Count of positions/points.
 *
 * @warning Be aware of pointers and count, there are no checking and can crash on overflow!
 */
static void draw_points_float(GLfloat *t_posX, GLfloat *t_posY, size_t t_count) {
  glBegin(GL_POINTS);
  for (size_t i = 0; i < t_count; ++i) {
    glVertex2f(t_posX[i], t_posY[i]);
  }
  glEnd();
}

/**
 * Draw multiple point/pixel on window with double position.
 *
 * @param t_posX Pointer of positions X in window as Double.
 * @param t_posY Pointer of positions Y in window as Double.
 * @param t_count Count of positions/points.
 *
 * @warning Be aware of pointers and count, there are no checking and can crash on overflow!
 */
static void draw_points_double(GLdouble *t_posX, GLdouble *t_posY, size_t t_count) {
  glBegin(GL_POINTS);
  for (size_t i = 0; i < t_count; ++i) {
    glVertex2d(t_posX[i], t_posY[i]);
  }
  glEnd();
}

/**
 * Draw line.
 *
 * @param t_beginX Begin position X in window as Integer.
 * @param t_beginY Begin position Y in window as Integer.
 * @param t_endX End position X in window as Integer.
 * @param t_endY End position Y in window as Integer.
 */
static void draw_line_int(GLint t_beginX, GLint t_beginY, GLint t_endX, GLint t_endY) {
  glBegin(GL_LINE_LOOP);
  glVertex2i(t_beginX, t_beginY);
  glVertex2i(t_endX, t_endY);
  glEnd();
}

/**
 * Draw rectangle lines with integer position.
 *
 * @param t_beginX Begin position X in window as Integer.
 * @param t_beginY Begin position Y in window as Integer.
 * @param t_endX End position X in window as Integer.
 * @param t_endY End position Y in window as Integer.
 */
static void draw_rectangle_int(GLint t_beginX, GLint t_beginY, GLint t_endX, GLint t_endY) {
  glBegin(GL_LINE_LOOP);
  glVertex2i(t_beginX, t_beginY);
  glVertex2i(t_endX, t_beginY);
  glVertex2i(t_endX, t_endY);
  glVertex2i(t_beginX, t_endY);
  glEnd();
}

/**
 * Draw rectangle lines on window with float position.
 *
 * @param t_beginX Begin position X in window as Float.
 * @param t_beginY Begin position Y in window as Float.
 * @param t_endX End position X in window as Float.
 * @param t_endY End position Y in window as Float.
 */
static void draw_rectangle_float(GLfloat t_beginX, GLfloat t_beginY, GLfloat t_endX, GLfloat t_endY) {
  glBegin(GL_LINE_LOOP);
  glVertex2f(t_beginX, t_beginY);
  glVertex2f(t_endX, t_beginY);
  glVertex2f(t_endX, t_endY);
  glVertex2f(t_beginX, t_endY);
  glEnd();
}

/**
 * Draw rectangle lines on window with double position.
 *
 * @param t_beginX Begin position X in window as Double.
 * @param t_beginY Begin position Y in window as Double.
 * @param t_endX End position X in window as Double.
 * @param t_endY End position Y in window as Double.
 */
static void draw_rectangle_double(GLdouble t_beginX, GLdouble t_beginY, GLdouble t_endX, GLdouble t_endY) {
  glBegin(GL_LINE_LOOP);
  glVertex2d(t_beginX, t_beginY);
  glVertex2d(t_endX, t_beginY);
  glVertex2d(t_endX, t_endY);
  glVertex2d(t_beginX, t_endY);
  glEnd();
}

/**
 * Draw filled rectangle on window with integer position.
 *
 * @param t_beginX Begin position X in window as Integer.
 * @param t_beginY Begin position Y in window as Integer.
 * @param t_endX End position X in window as Integer.
 * @param t_endY End position Y in window as Integer.
 */
static void draw_rectangle_filled_int(GLint t_beginX, GLint t_beginY, GLint t_endX, GLint t_endY) {
  glBegin(GL_QUADS);
  glVertex2i(t_beginX, t_beginY);
  glVertex2i(t_endX, t_beginY);
  glVertex2i(t_endX, t_endY);
  glVertex2i(t_beginX, t_endY);
  glEnd();
}

/**
 * Draw circle with line loop
 * SOURCE https://stackoverflow.com/a/24843626
 *
 * @param t_beginX Begin position X in window as Integer
 * @param t_beginY Begin position Y in window as Integer
 * @param t_radius Circle radius
 * @param t_segments Circle segments
 */
static void draw_circle_int(GLint t_beginX, GLint t_beginY, float t_radius, int t_segments) {
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < t_segments; i++) {
    const float theta = (s_jadeitite_pi * (float) i) / (float) t_segments;//get the current angle
    const float x = t_radius * cosf(theta);//calculate the x component
    const float y = t_radius * sinf(theta);//calculate the y component
    const int posX = (int) x + t_beginX;
    const int posY = (int) y + t_beginY;
    glVertex2i(posX, posY);//output vertex
  }
  glEnd();
}

/**
 * Draw filled circle with filled triangles
 * SOURCE https://stackoverflow.com/a/24843626
 *
 * @param t_beginX Begin position X in window as Integer
 * @param t_beginY Begin position Y in window as Integer
 * @param t_radius Circle radius
 * @param t_segments Circle segments
 */
static void draw_circle_filled_int(GLint t_beginX, GLint t_beginY, float t_radius, int t_segments) {
  glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
  glVertex2i(t_beginX, t_beginY); // center of circle
  for (int i = 0; i <= t_segments; i++) {
    const int posX = t_beginX + (int) (t_radius * cosf((float) i * s_jadeitite_pi / (float) t_segments));
    const int posY = t_beginY + (int) (t_radius * sinf((float) i * s_jadeitite_pi / (float) t_segments));
    glVertex2i(posX, posY);
  }
  glEnd(); //END
}

/**
 * Draw bitmap (8 * t_sizeY) on window with integer position.
 *
 * @param t_bitmap Bitmap with X size of char (8 bit).
 * @param t_sizeY Count of rows in bitmaps.
 * @param t_posX Position X in window as Integer.
 * @param t_posY Position Y in window as Integer.
 */
static void draw_bitmap_uchar(const unsigned char *t_bitmap, GLint t_sizeY, GLint t_posX, GLint t_posY) {
  for (GLint y = 0; y < t_sizeY; y++) {
    for (GLint x = 0; x < 8; x++) {
      const GLint set = t_bitmap[y] & 1 << x;
      if (set > 0) {
        glBegin(GL_POINTS);
        glVertex2i(t_posX + x, t_posY + y);
        glEnd();
      }
    }
  }
}

static void draw_triangle_int(vec_3_s32 t_vertices[3]) {
  glBegin(GL_TRIANGLES);
  glVertex3i(t_vertices[0].x, t_vertices[0].y, t_vertices[0].z);
  glVertex3i(t_vertices[1].x, t_vertices[1].y, t_vertices[1].z);
  glVertex3i(t_vertices[2].x, t_vertices[2].y, t_vertices[2].z);
  glEnd();
}

//======================================
//           Entry point
//======================================

#define JADEITITE_VER_MAJOR 0
#define JADEITITE_VER_MINOR 1
#define JADEITITE_VER_PATCH 0

// Framework version date YYYYMMDD
#define JADEITITE_VER_DATE 20220604

/**
 * Function for setting up callbacks and window properties for APP.
 *
 * @param p_callbacks Callbacks function
 * @param p_winProp Windows properties
 * @param p_argc Argument count
 * @param p_argv Argument list
 *
 * @return Return error code, 0 as PASSED, otherwise as FAILED
 *
 * @see t_callbacks
 */
extern int setup(callbacks_t *p_callbacks, winProp_t *p_winProp, int p_argc, char *p_argv[]);

int main(int argc, char *argv[]) {
  LOG_INFO(
      "Jadeitite framework - [%d.%d.%d - %d]",
      JADEITITE_VER_MAJOR,
      JADEITITE_VER_MINOR,
      JADEITITE_VER_PATCH,
      JADEITITE_VER_DATE
  );

  callbacks_t l_callbacks;

  int l_setup = setup(&l_callbacks, &g_jadeitite_windowProperties, argc, argv);

  if (l_setup) {
    window_init(argc, argv);
    l_callbacks.onAttach(argc, argv);
    window_run(&l_callbacks, &g_jadeitite_windowProperties);
    l_callbacks.onDetach(argc, argv);
  }

  LOG_INFO("Closing Jadeitite framework");
  return 0;
}

#endif //JADEITITE_H
