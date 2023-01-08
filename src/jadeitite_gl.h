#ifndef JADEITITE_GL_FRAMEWORK_H
#define JADEITITE_GL_FRAMEWORK_H

// =====================================================================================================================
//                                          SDL2 with Window and Renderer
// =====================================================================================================================
// SDL2 with Window and Renderer implementation for applications.
// ---------------------------------------------------------------------------------------------------------------------

#include "jadeitite.h"
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>

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
  void (*onAttach)(int, char **);
  void (*onDetach)(int, char **);
  void (*onResize)(int, int);
} jdt_callbacks_t;

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
  unsigned char renderMultiplier;
} jdt_winProp_t;

static inline void jdt_set_render_color(u8 r, u8 g, u8 b) {
  glColor3ub(r, g, b);
}

static inline void render_set_clear_color(GLclampf r, GLclampf g, GLclampf b) {
  glClearColor(r, g, b, 1.0f);
}

/**
 * Clear window
 */
static inline void jdt_render_begin(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Swap render buffer
 */
static inline void jdt_render_end(void) {
  glutSwapBuffers();
}

static u8 jdt_window_init(int p_argc, char *p_argv[], jdt_winProp_t p_winProp) {
  glutInit(&p_argc, p_argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(
    p_winProp.width,
    p_winProp.height
  );
  glutCreateWindow(p_winProp.label);
  glutSetOption(
    GLUT_ACTION_ON_WINDOW_CLOSE,
    GLUT_ACTION_GLUTMAINLOOP_RETURNS
  );

  JDT_LOG_DEBUG("Glut Window initialize successfully");
  return JDT_RS_OK;
}

static u8 jdt_window_run(jdt_callbacks_t *p_callbacks, jdt_winProp_t *p_winProp, int argc, char *argv[]) {
  glutDisplayFunc(p_callbacks->onUpdate);
  if (p_winProp->autoRefresh) {
    glutIdleFunc(p_callbacks->onUpdate);
  } else {
    glutIgnoreKeyRepeat(1);
  }
  glutReshapeFunc(p_callbacks->onResize);
  glutKeyboardFunc(p_callbacks->onKeyboardDown);
  glutKeyboardUpFunc(p_callbacks->onKeyboardUp);
  glutMainLoop();

  return JDT_RS_OK;
}

/**
 * Set Glut projection to 2D perspective
 */
static void render_set_projection_2DOrthographic(
  double p_window_width,
  double p_window_height
) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(
    0,
    p_window_width,
    p_window_height,
    0
  );
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/**
 * Set Glut projection to 3D perspective.
 *
 * @param p_width Usually set to window p_width/X.
 * @param p_height Usually se to window p_height/Y.
 * @param p_fov Set field of view.
 * @param p_zNear Set minimum render distance from view point.
 * @param p_zFar Set maximum render distance from view point.
 */
static void render_set_projection_3DPerspective(
  GLdouble p_width,
  GLdouble p_height,
  GLdouble p_fov,
  GLdouble p_zNear,
  GLdouble p_zFar
) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(p_fov, p_width / p_height, p_zNear, p_zFar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static inline void jdt_draw_point(s32 x, s32 y) {
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

/**
 * Draw point/pixel on window with integer position fastly.
 *
 * @param p_posX Position X in window as Integer.
 * @param p_posY Position Y in window as Integer.
 */
static inline void jdt_draw_point_fast_l1_int(int p_posX, int p_posY) {
  glBegin(GL_POINTS);
  glVertex2i(p_posX, p_posY);
  glEnd();
}

/**
 * Draw point/pixel on window with integer position fastly.
 *
 * @warning Before and after all point do glBegin(GL_POINTS) and glEnd()
 *
 * @param p_posX Position X in window as Integer.
 * @param p_posY Position Y in window as Integer.
 */
static inline void jdt_draw_point_fast_l2_int(int p_posX, int p_posY) {
  glVertex2i(p_posX, p_posY);
}


/**
 * Draw line.
 *
 * @param p_beginX Begin position X in window as Integer.
 * @param p_beginY Begin position Y in window as Integer.
 * @param p_endX End position X in window as Integer.
 * @param p_endY End position Y in window as Integer.
 */
static void jdt_draw_line_int(
  int p_beginX,
  int p_beginY,
  int p_endX,
  int p_endY
) {
  glBegin(GL_LINE_LOOP);
  glVertex2i(p_beginX, p_beginY);
  glVertex2i(p_endX, p_endY);
  glEnd();
}


/**
 * Draw rectangle lines with integer position.
 *
 * @param p_beginX Begin position X in window as Integer.
 * @param p_beginY Begin position Y in window as Integer.
 * @param p_endX End position X in window as Integer.
 * @param p_endY End position Y in window as Integer.
 */
static void jdt_draw_rectangle_int(
  int p_beginX,
  int p_beginY,
  int p_endX,
  int p_endY
) {
  glBegin(GL_LINE_LOOP);
  glVertex2i(p_beginX, p_beginY);
  glVertex2i(p_endX, p_beginY);
  glVertex2i(p_endX, p_endY);
  glVertex2i(p_beginX, p_endY);
  glEnd();
}

/**
 * Draw filled rectangle on window with integer position.
 *
 * @param p_beginX Begin position X in window as Integer.
 * @param p_beginY Begin position Y in window as Integer.
 * @param p_endX End position X in window as Integer.
 * @param p_endY End position Y in window as Integer.
 */
static void jdt_draw_rectangle_filled_int(
  int p_beginX,
  int p_beginY,
  int p_endX,
  int p_endY
) {
  glBegin(GL_QUADS);
  glVertex2i(p_beginX, p_beginY);
  glVertex2i(p_endX, p_beginY);
  glVertex2i(p_endX, p_endY);
  glVertex2i(p_beginX, p_endY);
  glEnd();
}

/**
 * Draw circle with line loop
 * SOURCE https://stackoverflow.com/a/24843626
 *
 * @param p_beginX Begin position X in window as Integer
 * @param p_beginY Begin position Y in window as Integer
 * @param p_radius Circle radius
 * @param p_segments Circle segments
 */
static void jdt_draw_circle_int(
  s32 p_beginX,
  s32 p_beginY,
  f32 p_radius,
  s32 p_segments
) {
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < p_segments; i++) {
    //get the current angle
    const f32 theta = (JDT_MATH_2PI * (f32) i) / (f32) p_segments;
    const f32 x = p_radius * cosf(theta);//calculate the x component
    const f32 y = p_radius * sinf(theta);//calculate the y component
    const s32 posX = (s32) x + p_beginX;
    const s32 posY = (s32) y + p_beginY;
    glVertex2i(posX, posY);//output vertex
  }
  glEnd();
}

/**
 * Draw filled circle with filled triangles
 * SOURCE https://stackoverflow.com/a/24843626
 *
 * @param p_beginX Begin position X in window as Integer
 * @param p_beginY Begin position Y in window as Integer
 * @param p_radius Circle radius
 * @param p_segments Circle segments
 */
static void jdt_draw_circle_filled_int(
  int p_beginX,
  int p_beginY,
  float p_radius,
  int p_segments
) {
  glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
  glVertex2i(p_beginX, p_beginY); // center of circle
  for (int i = 0; i <= p_segments; i++) {
    const int posX = p_beginX + (int) (
      p_radius * cosf((float) i *
        JDT_MATH_2PI / (float) p_segments
      ));
    const int posY = p_beginY + (int) (
      p_radius * sinf((float) i *
        JDT_MATH_2PI / (float) p_segments
      ));
    glVertex2i(posX, posY);
  }
  glEnd(); //END
}

static void jdt_draw_triangle_int(int p_vertices[3][3]) {
  glBegin(GL_TRIANGLES);
  glVertex3i(p_vertices[0][0], p_vertices[0][1], p_vertices[0][2]);
  glVertex3i(p_vertices[1][0], p_vertices[1][1], p_vertices[1][2]);
  glVertex3i(p_vertices[2][0], p_vertices[2][1], p_vertices[2][2]);
  glEnd();
}

/**
 * Draw bitmap (8 * p_sizeY) on window with integer position.
 *
 * @param p_bitmap Bitmap with X size of char (8 bit).
 * @param p_sizeY Count of rows in bitmaps.
 * @param p_posX Position X in window as Integer.
 * @param p_posY Position Y in window as Integer.
 */
static void jdt_draw_bitmap(
  u32 p_width,
  u32 p_height,
  const u8 p_bitmap[p_width],
  u32 p_posX,
  u32 p_posY
) {
  for (int y = 0; y < p_height; y++) {
    for (int x = 0; x < 8; x++) {
      const int set = p_bitmap[y] & 1 << x;
      if (set > 0) {
        jdt_draw_point(p_posX + x, p_posY + y);
      }
    }
  }
}

static void jdt_draw_bitmaps(u32 p_height, u32 p_width, const u8 p_bitmap[][p_height], u32 p_x, u32 p_y, char *p_text) {
  size_t l_textLen = strlen(p_text);
  for (int x = 0; x < l_textLen; x++) {
    jdt_draw_bitmap(p_width, p_height, p_bitmap[p_text[x]], p_x + (p_width * x), p_y);
  }
}

#endif //JADEITITE_GL_FRAMEWORK_H
