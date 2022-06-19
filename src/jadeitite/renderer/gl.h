#ifndef JADEITITE_GL_H
#define JADEITITE_GL_H

#include <GL/gl.h>
#include "jadeitite/sys.h"

//======================================
//          OpenGl drawing
//======================================

void draw_point_int(int p_posX, int p_posY);
void draw_points_int(int *p_posX, int *p_posY, size_t p_count);
void draw_line_int(int p_beginX, int p_beginY, int p_endX, int p_endY);
void draw_rectangle_int(int p_beginX, int p_beginY, int p_endX, int p_endY);
void draw_rectangle_filled_int(int p_beginX, int p_beginY, int p_endX, int p_endY);
void draw_circle_int(int p_beginX, int p_beginY, float p_radius, int p_segments);
void draw_circle_filled_int(int p_beginX, int p_beginY, float p_radius, int p_segments);
void draw_bitmap_uchar(const unsigned char *p_bitmap, int p_sizeY, int p_posX, int p_posY);

//======================================
//        OpenGl fast drawing
//======================================

/**
 * Draw point/pixel on window with integer position fastly.
 *
 * @param p_posX Position X in window as Integer.
 * @param p_posY Position Y in window as Integer.
 */
static inline void draw_point_fast_l1_int(int p_posX, int p_posY) {
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
static inline void draw_point_fast_l2_int(int p_posX, int p_posY) {
  glVertex2i(p_posX, p_posY);
}

//======================================
//         OpenGl fast utils
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
 * In case if we will have problem with rendering/drawing corner with primitive drawing lines,
 * then use this function onAttach.
 */
static inline void render_fix_corner(void) {
  glTranslatef(0.5f, 0.5f, 0);
}

#endif //JADEITITE_GL_H
