#ifndef ALCHEMIST_JADEITITE_GLUT_H
#define ALCHEMIST_JADEITITE_GLUT_H

#include <GL/freeglut.h>

//======================================
//             Structures
//======================================

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
