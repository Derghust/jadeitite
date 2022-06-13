#ifndef JADEITITE_ENTRYPOINT_H
#define JADEITITE_ENTRYPOINT_H

#include "jadeitite_glut.h"
#include "jadeitite_log.h"
#include "jadeitite_config.h"

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

int main(int argc, char *argv[]) {
  LOG_INFO(
    "Jadeitite framework - [%d.%d.%d - %d]",
    JADEITITE_VER_MAJOR,
    JADEITITE_VER_MINOR,
    JADEITITE_VER_PATCH,
    JADEITITE_VER_DATE
  );

  callbacks_t l_callbacks;
  winProp_t l_windProp;

  int l_setup = setup(&l_callbacks, &l_windProp, argc, argv);

  if (l_setup) {
    window_init(argc, argv, l_windProp);
    l_callbacks.onAttach(argc, argv);
    window_run(l_callbacks, l_windProp);
    l_callbacks.onDetach(argc, argv);
  }

  LOG_INFO("Closing Jadeitite framework");
  return 0;
}

#endif //JADEITITE_ENTRYPOINT_H
