#include "entrypoint_glut.h"

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
