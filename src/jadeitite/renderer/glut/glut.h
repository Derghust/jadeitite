#ifndef ALCHEMIST_JADEITITE_GLUT_H
#define ALCHEMIST_JADEITITE_GLUT_H

#include <GL/freeglut.h>
#include "jadeitite/renderer/window.h"
#include "jadeitite/renderer/callbacks.h"

//======================================
//            Glut engine
//======================================

void window_run(callbacks_t p_callbacks, winProp_t p_winProp);
void window_init(int p_argc, char *p_argv[], winProp_t p_winProp);
void window_resize(int p_width, int p_height);

//======================================
//          Glut projections
//======================================

void render_set_projection_2DOrthographic(
  double p_window_width,
  double p_window_height
);
void render_set_projection_3DPerspective(
  GLdouble p_width,
  GLdouble p_height,
  GLdouble p_fov,
  GLdouble p_zNear,
  GLdouble p_zFar
);

//======================================
//            Glut fast
//======================================
// Glut inline function for best
// performance
//======================================

/**
 * Swap render buffer
 */
static inline void render_end(void) {
  glutSwapBuffers();
}

#endif //ALCHEMIST_JADEITITE_GLUT_H
