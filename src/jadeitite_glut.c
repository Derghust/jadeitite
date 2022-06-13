#include "jadeitite_glut.h"

//======================================
//            Glut window
//======================================

/**
 * Function will set up windows from user defined windows properties
 * and call an callbacks.
 *
 * @param p_callbacks App callbacks (onUpdate, onKeyboardDown, onKeyboardUp, onAttach, onDetach).
 * @param p_winProp Window properties.
 */
void window_run(callbacks_t p_callbacks, winProp_t p_winProp) {
  glutDisplayFunc(p_callbacks.onUpdate);
  if (p_winProp.autoRefresh) {
    glutIdleFunc(p_callbacks.onUpdate);
  } else {
    glutIgnoreKeyRepeat(1);
  }
  glutReshapeFunc(p_callbacks.onResize);
  glutKeyboardFunc(p_callbacks.onKeyboardDown);
  glutKeyboardUpFunc(p_callbacks.onKeyboardUp);
  glutMainLoop();
}

/**
 * Initialize window with glut
 * Set glut display with flag RGB | DOUBLE (buffer) | DEPTH
 * Initialize window size with static window properties
 * Create window with label from static window properties
 * And lastly set callback on window close
 *
 * @param p_argc Argument counter from main function
 * @param p_argv Array of argument string from main function
 */
void window_init(int p_argc, char *p_argv[], winProp_t p_winProp) {
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
}

/**
 * Resize window with glut reshape window and write current setting to static
 * window properties
 *
 * @param p_width
 * @param p_height
 */
void window_resize(int p_width, int p_height) {
  glutReshapeWindow(
    p_width,
    p_height
  );
}

//======================================
//          Glut projections
//======================================

/**
 * Set Glut projection to 2D perspective
 */
void render_set_projection_2DOrthographic(
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
void render_set_projection_3DPerspective(
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
