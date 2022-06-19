#ifndef JADEITITE_DT_H
#define JADEITITE_DT_H

//======================================
//           Data types
//======================================

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef char s8;
typedef short s16;
typedef int s32;
typedef long s64;

typedef float f32;
typedef double f64;

typedef u8 byte;
typedef u16 word;
typedef u32 dword;

//======================================
//           Enumerators
//======================================

typedef enum {
  RS_OK = 0,
  RS_FAILED = 1,

  RS_MEMORY_OVERFLOW = 100,

  RS_UNKNOWN_STATUS = 999,
} return_status_e;

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

typedef struct {
  f64 x, y;
} vec_2_f64;

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

typedef struct {
  s8 x, y, z;
} vec_3_s8;

typedef struct {
  s16 x, y, z;
} vec_3_s16;

typedef struct {
  s32 x, y, z;
} vec_3_s32;

typedef struct {
  f32 x, y, z;
} vec_3_f32;

typedef struct {
  f64 x, y, z;
} vec_3_f64;

#endif //JADEITITE_DT_H
