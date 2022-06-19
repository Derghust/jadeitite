#include "string.h"

/**
 * Convert integer with user defined base to String
 *
 * Source: https://www.strudel.org.uk/itoa/
 *
 * @param p_number Number, e.g. 5, 6, 20, 100, ...
 * @param p_base Base number, e.g. 10, 16 (HEX), ...
 * @return
 */
char *int_to_str(int p_number, int p_base) {
  if (p_number == 0) {
    return "0";
  } else {
    static char buf[32] = {0};
    int i = 30;
    for (; p_number && i; --i, p_number /= p_base)
      buf[i] = "0123456789abcdef"[p_number % p_base];
    return &buf[i + 1];
  }
}
