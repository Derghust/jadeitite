#ifndef JADEITITE_DT_H
#define JADEITITE_DT_H

#include "jadeitite/sys.h"

//======================================
//           Data types
//======================================

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#ifdef SYS64
typedef unsigned long u64;
#endif

typedef char s8;
typedef short s16;
typedef int s32;
#ifdef SYS64
typedef long s64;
#endif

typedef float f32;
#ifdef SYS64
typedef double f64;
#endif

typedef u8 byte;
typedef u16 word;
typedef u32 dword;

typedef u8 bool;
#define TRUE 1;
#define FALSE 0;
#define true 1;
#define false 0;

//======================================
//           Enumerators
//======================================

/**
 * Used for function return flag as u8/byte
 */
#define RS_OK     0
#define RS_FAILED 1

//======================================
//             Structures
//======================================

//--------------------------------------
//          General structures
//--------------------------------------

typedef struct {
  u8 r, g, b;
} color_t;

//--------------------------------------
//               Vector 2
//--------------------------------------

typedef struct {
  u8 x, y;
} vec_2_u8;

typedef struct {
  u16 x, y;
} vec_2_u16;

typedef struct {
  u32 x, y;
} vec_2_u32;

typedef struct {
  s8 x, y;
} vec_2_s8;

typedef struct {
  s16 x, y;
} vec_2_s16;

typedef struct {
  s32 x, y;
} vec_2_s32;

typedef struct {
  f32 x, y;
} vec_2_f32;

#ifdef SYS64
typedef struct {
  f64 x, y;
} vec_2_f64;
#endif

//--------------------------------------
//               Vector 3
//--------------------------------------

typedef struct {
  u8 x, y, z;
} vec_3_u8;

typedef struct {
  u16 x, y, z;
} vec_3_u16;

typedef struct {
  u32 x, y, z;
} vec_3_u32;

#ifdef SYS64
typedef struct {
  u64 x, y, z;
} vec_3_u64;
#endif

typedef struct {
  s8 x, y, z;
} vec_3_s8;

typedef struct {
  s16 x, y, z;
} vec_3_s16;

typedef struct {
  s32 x, y, z;
} vec_3_s32;

#ifdef SYS64
typedef struct {
  s64 x, y, z;
} vec_3_s64;
#endif

typedef struct {
  f32 x, y, z;
} vec_3_f32;

#ifdef SYS64
typedef struct {
  f64 x, y, z;
} vec_3_f64;
#endif

/*============================================================================*/
/*                           Special functions                                */
/*============================================================================*/

static inline u8 get_bit(u32 l_data, u32 l_pos) {
  return (l_data >> l_pos) & 1;
}

#endif //JADEITITE_DT_H
