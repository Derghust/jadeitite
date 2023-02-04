#include "jadeitite.h"
#include "font8x8.h"

int main(void) {
  jdt_asset_create("font8x8.dat", 128, 8, font8x8_basic);

  return 0;
}
