#ifndef JADEITITE_ENTRYPOINT_FRAMEWORK_H
#define JADEITITE_ENTRYPOINT_FRAMEWORK_H

// =====================================================================================================================
//                                               EntryPoint
// =====================================================================================================================
// Main entrypoint for Jadeitite library. Main function is implemented HERE.
// ---------------------------------------------------------------------------------------------------------------------

#include "jadeitite.h"
#include "jadeitite_gl.h"

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
extern int jdt_setup(
  jdt_callbacks_t *p_callbacks,
  jdt_winProp_t *p_winProp,
  int p_argc,
  char *p_argv[]
);

int main(int argc, char *argv[]) {
  JDT_LOG_INFO(
    "Jadeitite framework - [%d.%d.%d]",
    JADEITITE_VER_MAJOR,
    JADEITITE_VER_MINOR,
    JADEITITE_VER_PATCH
  );

  jdt_callbacks_t l_callbacks;
  jdt_winProp_t l_windProp;

  int l_setup = jdt_setup(&l_callbacks, &l_windProp, argc, argv);

  if (l_setup == JDT_RS_OK) {
    jdt_window_init(argc, argv, l_windProp);
    l_callbacks.onAttach(argc, argv);
    jdt_window_run(&l_callbacks, &l_windProp, argc, argv);
    l_callbacks.onDetach(argc, argv);
  }

  JDT_LOG_INFO("Closing Jadeitite framework");
  return 0;
}

#endif //JADEITITE_ENTRYPOINT_FRAMEWORK_H
