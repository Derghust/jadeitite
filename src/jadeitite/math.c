#include "math.h"

//======================================
//           RNG & Noise
//======================================

/**
 * Squirrel3
 * Link: https://www.youtube.com/watch?v=LWFzPP8ZbdU
 */
u32 squirrel3(u32 p_index, u32 p_seed) {
  const u32 l_bit_noise_1 = 0x68E31DA4;
  const u32 l_bit_noise_2 = 0xB5297A4D;
  const u32 l_bit_noise_3 = 0x1B56C4E9;

  u32 l_mangledBits = p_index;
  l_mangledBits *= l_bit_noise_1;
  l_mangledBits += p_seed;
  l_mangledBits ^= (l_mangledBits >> 8);
  l_mangledBits += l_bit_noise_2;
  l_mangledBits ^= (l_mangledBits << 8);
  l_mangledBits *= l_bit_noise_3;
  l_mangledBits ^= (l_mangledBits >> 8);

  return l_mangledBits;
}

//======================================
//            Math utils
//======================================

s8 abs_s8(s8 p_value) {
  if (p_value < 0) { return p_value *= -1; } else { return p_value; }
}
s16 abs_s16(s16 p_value) {
  if (p_value < 0) { return p_value *= -1; } else { return p_value; }
}
s32 abs_s32(s32 p_value) {
  if (p_value < 0) { return p_value *= -1; } else { return p_value; }
}
s64 abs_s64(s64 p_value) {
  if (p_value < 0) { return p_value *= -1; } else { return p_value; }
}

s8 min_s8(s8 p_value, s8 p_min) {
  if (p_value < p_min) { return p_min; } else { return p_value; }
}
s16 min_s16(s16 p_value, s16 p_min) {
  if (p_value < p_min) { return p_min; } else { return p_value; }
}
s32 min_s32(s32 p_value, s32 p_min) {
  if (p_value < p_min) { return p_min; } else { return p_value; }
}
s64 min_s64(s64 p_value, s64 p_min) {
  if (p_value < p_min) { return p_min; } else { return p_value; }
}

s8 max_s8(s8 p_value, s8 p_max) {
  if (p_value > p_max) { return p_max; } else { return p_value; }
}
s16 max_s16(s16 p_value, s16 p_max) {
  if (p_value > p_max) { return p_max; } else { return p_value; }
}
s32 max_s32(s32 p_value, s32 p_max) {
  if (p_value > p_max) { return p_max; } else { return p_value; }
}
s64 max_s64(s64 p_value, s64 p_max) {
  if (p_value > p_max) { return p_max; } else { return p_value; }
}

s8 threshold_s8(s8 p_value, s8 p_min, s8 p_max) {
  if (p_value < p_min) { return p_min; }
  if (p_value > p_max) { return p_max; }
  return p_value;
}
s16 threshold_s16(s16 p_value, s16 p_min, s16 p_max) {
  if (p_value < p_min) { return p_min; }
  if (p_value > p_max) { return p_max; }
  return p_value;
}
s32 threshold_s32(s32 p_value, s32 p_min, s32 p_max) {
  if (p_value < p_min) { return p_min; }
  if (p_value > p_max) { return p_max; }
  return p_value;
}
s64 threshold_s64(s64 p_value, s64 p_min, s64 p_max) {
  if (p_value < p_min) { return p_min; }
  if (p_value > p_max) { return p_max; }
  return p_value;
}
