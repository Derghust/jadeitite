#ifndef JADEITITE_ENTRYPOINT_H
#define JADEITITE_ENTRYPOINT_H

#include "jadeitite/log.h"
#include "jadeitite/config.h"
#include "jadeitite/renderer/window.h"
#include "jadeitite/renderer/callbacks.h"

#include "jadeitite/renderer/glut/gl.h"
#include "jadeitite/renderer/glut/glut.h"

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
extern int setup(
  callbacks_t *p_callbacks,
  winProp_t *p_winProp,
  int p_argc,
  char *p_argv[]
);

#endif //JADEITITE_ENTRYPOINT_H
