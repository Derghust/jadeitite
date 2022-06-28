#include "sdl2.h"

int main(int argc, char *argv[]) {
  LOG_INFO(
    "Jadeitite framework - [%d.%d.%d - %d]",
    JADEITITE_VER_MAJOR,
    JADEITITE_VER_MINOR,
    JADEITITE_VER_PATCH,
    JADEITITE_VER_DATE
  );

  LOG_INFO("Closing Jadeitite framework");
  return 0;
}
