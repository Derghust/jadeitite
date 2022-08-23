#include "gl.h"

#include <math.h>
#include "jadeitite/math.h"

//======================================
//          OpenGl drawing
//======================================

/**
 * Draw point/pixel on window with integer position.
 *
 * @param p_posX Position X in window as Integer.
 * @param p_posY Position Y in window as Integer.
 */
void draw_point_int(int p_posX, int p_posY) {
  glBegin(GL_POINTS);
  glVertex2i(p_posX, p_posY);
  glEnd();
}

/**
 * Draw multiple point/pixel on window with integer position.
 *
 * @param p_posX Pointer of positions X in window as Integer.
 * @param p_posY Pointer of positions Y in window as Integer.
 * @param p_count Count of positions/points.
 *
 * @warning Be aware of pointers and count, there are no checking and can crash on overflow!
 */
void draw_points_int(int *p_posX, int *p_posY, u32 p_count) {
  glBegin(GL_POINTS);
  for (u32 i = 0; i < p_count; ++i) {
    glVertex2i(p_posX[i], p_posY[i]);
  }
  glEnd();
}

/**
 * Draw line.
 *
 * @param p_beginX Begin position X in window as Integer.
 * @param p_beginY Begin position Y in window as Integer.
 * @param p_endX End position X in window as Integer.
 * @param p_endY End position Y in window as Integer.
 */
void draw_line_int(
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
void draw_rectangle_int(
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
void draw_rectangle_filled_int(
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
void draw_circle_int(
  s32 p_beginX,
  s32 p_beginY,
  f32 p_radius,
  s32 p_segments
) {
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < p_segments; i++) {
    //get the current angle
    const f32 theta = (s_2pi * (f32) i) / (f32) p_segments;
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
void draw_circle_filled_int(
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
        s_2pi / (float) p_segments
      ));
    const int posY = p_beginY + (int) (
      p_radius * sinf((float) i *
        s_2pi / (float) p_segments
      ));
    glVertex2i(posX, posY);
  }
  glEnd(); //END
}

/**
 * Draw bitmap (8 * p_sizeY) on window with integer position.
 *
 * @param p_bitmap Bitmap with X size of char (8 bit).
 * @param p_sizeY Count of rows in bitmaps.
 * @param p_posX Position X in window as Integer.
 * @param p_posY Position Y in window as Integer.
 */
void draw_bitmap_uchar(
  const unsigned char *p_bitmap,
  int p_sizeY,
  int p_posX,
  int p_posY
) {
  for (int y = 0; y < p_sizeY; y++) {
    for (int x = 0; x < 8; x++) {
      const int set = p_bitmap[y] & 1 << x;
      if (set > 0) {
        glBegin(GL_POINTS);
        glVertex2i(p_posX + x, p_posY + y);
        glEnd();
      }
    }
  }
}

static void draw_triangle_int(int p_vertices[3][3]) {
  glBegin(GL_TRIANGLES);
  glVertex3i(p_vertices[0][0], p_vertices[0][1], p_vertices[0][2]);
  glVertex3i(p_vertices[1][0], p_vertices[1][1], p_vertices[1][2]);
  glVertex3i(p_vertices[2][0], p_vertices[2][1], p_vertices[2][2]);
  glEnd();
}
