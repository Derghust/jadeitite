#include "jadeitite_math.h"

//======================================
//           RNG & Noise
//======================================

/**
 * Squirrel3
 * Link: https://www.youtube.com/watch?v=LWFzPP8ZbdU
 */
unsigned int squirrel3(unsigned int p_index, unsigned int p_seed) {
  const unsigned int l_bit_noise_1 = 0x68E31DA4;
  const unsigned int l_bit_noise_2 = 0xB5297A4D;
  const unsigned int l_bit_noise_3 = 0x1B56C4E9;

  unsigned int l_mangledBits = p_index;
  l_mangledBits *= l_bit_noise_1;
  l_mangledBits += p_seed;
  l_mangledBits ^= (l_mangledBits >> 8);
  l_mangledBits += l_bit_noise_2;
  l_mangledBits ^= (l_mangledBits << 8);
  l_mangledBits *= l_bit_noise_3;
  l_mangledBits ^= (l_mangledBits >> 8);

  return l_mangledBits;
}
