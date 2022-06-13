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

#endif //JADEITITE_DT_H
