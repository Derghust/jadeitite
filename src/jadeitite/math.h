#ifndef JADEITITE_MATH_H
#define JADEITITE_MATH_H

#include "jadeitite/datatypes.h"

//======================================
//     Static mathematical variables
//======================================

static const f32 s_pi = 3.14159f;

//======================================
//           RNG & Noise
//======================================

u32 squirrel3(u32 p_index, u32 p_seed);

//======================================
//            Math utils
//======================================

s8 abs_s8(s8 p_value);
s16 abs_s16(s16 p_value);
s32 abs_s32(s32 p_value);
s64 abs_s64(s64 p_value);

s8 min_s8(s8 p_value, s8 p_min);
s16 min_s16(s16 p_value, s16 p_min);
s32 min_s32(s32 p_value, s32 p_min);
s64 min_s64(s64 p_value, s64 p_min);

s8 max_s8(s8 p_value, s8 p_max);
s16 max_s16(s16 p_value, s16 p_max);
s32 max_s32(s32 p_value, s32 p_max);
s64 max_s64(s64 p_value, s64 p_max);

s8 threshold_s8(s8 p_value, s8 p_min, s8 p_max);
s16 threshold_s16(s16 p_value, s16 p_min, s16 p_max);
s32 threshold_s32(s32 p_value, s32 p_min, s32 p_max);
s64 threshold_s64(s64 p_value, s64 p_min, s64 p_max);

#endif //JADEITITE_MATH_H
