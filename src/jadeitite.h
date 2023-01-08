#ifndef JADEITITE_FRAMEWORK_H
#define JADEITITE_FRAMEWORK_H

// =====================================================================================================================
//                                                     Macros
// =====================================================================================================================
// Specified macros for Jadeitite framework.
//
// Contains:
//  - Framework version
//    - JADEITITE_VER_XYZ where XYZ are MAJOR, MINOR and PATCH
//  - Framework version date
//    - JADEITITE_VER_DATE
// ---------------------------------------------------------------------------------------------------------------------

#define JADEITITE_VER_MAJOR 0
#define JADEITITE_VER_MINOR 5
#define JADEITITE_VER_PATCH 0

// =====================================================================================================================
//                                                    Logging
// =====================================================================================================================
// Lightweight logging framework with source linking and precision time.
//
// Examples:
//  JDT_LOG_INFO("This is my value %d", 123);
//  JDT_LOG_ERROR("This went wrong! [value=%x; error=%s]", error.value, error.message);
// ---------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

typedef enum {
  JDT_LOG_LEVEL_INFO,
  JDT_LOG_LEVEL_WARN,
  JDT_LOG_LEVEL_ERROR,
  JDT_LOG_LEVEL_FATAL,
  JDT_LOG_LEVEL_DEBUG
} jdt_log_level;

// src: https://stackoverflow.com/a/27678121
static void jdt_log_logTime(void) {
  char fmt[64];
  char buf[64];
  struct timeval tv;
  struct tm *tm;

  gettimeofday(&tv, NULL);
  tm = localtime(&tv.tv_sec);
  strftime(fmt, sizeof(fmt), "%H:%M:%S:%%06u", tm);
  snprintf(buf, sizeof(buf), fmt, tv.tv_usec);
  printf("[%s]", buf);
}

static void jdt_log_logSrc(const char *p_file, int p_line) {
  printf("[ %s:%d ]", p_file, p_line);
}

static void jdt_log_logLevel(jdt_log_level p_level) {
  switch (p_level) {
  case JDT_LOG_LEVEL_INFO:printf("[INFO]: ");
    break;
  case JDT_LOG_LEVEL_WARN:printf("[WARN]: ");
    break;
  case JDT_LOG_LEVEL_ERROR:printf("[ERROR]: ");
    break;
  case JDT_LOG_LEVEL_FATAL:printf("[FATAL]: ");
    break;
  case JDT_LOG_LEVEL_DEBUG:printf("[DEBUG]: ");
    break;
  default:printf("Undefined behaviour!\n");
    return;
  }
}

static void jdt_log_log(
  jdt_log_level p_level,
  const char *p_file,
  int p_line,
  const char *p_input,
  ...
) {
  jdt_log_logTime();
  jdt_log_logSrc(p_file, p_line);
  jdt_log_logLevel(p_level);
  va_list l_argList;
  va_start(l_argList, p_input);
  vprintf(p_input, l_argList);
  va_end(l_argList);
  printf("\n");
}

#define JDT_GET_SRC_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define JDT_LOG_INFO(...) jdt_log_log(JDT_LOG_LEVEL_INFO, JDT_GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define JDT_LOG_WARN(...) jdt_log_log(JDT_LOG_LEVEL_WARN, JDT_GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define JDT_LOG_ERROR(...) jdt_log_log(JDT_LOG_LEVEL_ERROR, JDT_GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define JDT_LOG_FATAL(...) jdt_log_log(JDT_LOG_LEVEL_FATAL, JDT_GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define JDT_LOG_DEBUG(...) jdt_log_log(JDT_LOG_LEVEL_DEBUG, JDT_GET_SRC_FILENAME , __LINE__, __VA_ARGS__)

// =====================================================================================================================
//                                                Primitives types
// =====================================================================================================================
// Primitive types for Jadeitite framework for more simpler and easy read for data types.
// ---------------------------------------------------------------------------------------------------------------------

// link: https://stackoverflow.com/questions/1505582/determining-32-vs-64-bit-in-c
// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define SYS64
#if defined(size_t)
typedef unsigned long size_t;
#endif
#else
#define SYS32
#if defined(size_t)
typedef unsigned int size_t;
#endif
#endif
#endif

// link: https://stackoverflow.com/questions/1505582/determining-32-vs-64-bit-in-c
// Check GCC and TCC
#if __GNUC__ || __TINYC__
#if __x86_64__ || __ppc64__
#define SYS64
#if defined(size_t)
typedef unsigned long size_t;
#endif
#else
#define SYS32
#if defined(size_t)
typedef unsigned int size_t;
#endif
#endif
#endif

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

#define JDT_RS_OK     0
#define JDT_RS_FAILED 1

// =====================================================================================================================
//                                               Memory operators
// =====================================================================================================================
// Memory operation for custom memory allocating.
//
// This memory operators is meant to be just as fun.
// ---------------------------------------------------------------------------------------------------------------------

#include <stdlib.h>

typedef struct jdt_mem_block_u16_rt {
  u16 start, end;
  void *data;
  struct jdt_mem_block_u16_rt *next;
} jdt_mem_block_u16_t;

static jdt_mem_block_u16_t *jdt_mem_u16_init(u16 p_max_size) {
  jdt_mem_block_u16_t *l_block = malloc(sizeof(jdt_mem_block_u16_t));
  l_block->next = NULL;
  l_block->data = NULL;
  l_block->start = 0;
  l_block->end = p_max_size;

  return l_block;
}

static void *jdt_mem_u16_alloc(
  jdt_mem_block_u16_t *p_mem_block,
  u16 p_size
) {
  const int l_calc = p_mem_block->start + p_size <= p_mem_block->end;
  if (p_mem_block->next == NULL && p_mem_block->data == NULL && l_calc) {
    jdt_mem_block_u16_t *l_block = malloc(sizeof(jdt_mem_block_u16_t));
    l_block->next = NULL;
    l_block->data = NULL;
    l_block->start = p_size + 1;
    l_block->end = p_mem_block->end;
    void *l_data = malloc(p_size);
    p_mem_block->data = l_data;
    p_mem_block->end = p_size;
    p_mem_block->next = l_block;
    return l_data;
  } else if (p_mem_block->next != NULL && l_calc) {
    return jdt_mem_u16_alloc(p_mem_block->next, p_size);
  } else {
    return NULL;
  }
}

static void jdt_mem_u16_free(jdt_mem_block_u16_t *p_mem_block) {
  if (p_mem_block->next == NULL) {
    if (p_mem_block->data != NULL) {
      free(p_mem_block->data);
    }
  } else {
    jdt_mem_u16_free(p_mem_block->next);
    if (p_mem_block->data != NULL) {
      free(p_mem_block->data);
    }
  }
  free(p_mem_block);
}

// =====================================================================================================================
//                                               File operators
// =====================================================================================================================
// File operation like read and write.
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Write any data type to file
 *
 * @param p_file_path File path with its file name and extension, e.g. data.dat
 * @param p_data Data
 * @param p_data_size Size of some data, e.g sizeof(my_struct)
 * @return Return JDT_RS_OK if write operation is successful, otherwise return JDT_RS_FAILED
 */
static u8 jdt_file_write(const char *p_file_path, void *p_data, size_t p_data_size) {
  FILE *l_file = fopen(p_file_path, "w");
  if (l_file == NULL) {
    JDT_LOG_ERROR("Failed to open file [file_path=%s]!", p_file_path);
    return JDT_RS_FAILED;
  }

  size_t l_status = fwrite(p_data, p_data_size, 1, l_file);
  if (l_status == 0) {
    JDT_LOG_ERROR(
      "Failed to write data to file [file_path=%s; data_size=%ul]",
      p_file_path, p_data_size);

    fclose(l_file);
    return JDT_RS_FAILED;
  }

  JDT_LOG_DEBUG("Successfully written data file [path=%s; size=%d]", p_file_path, p_data_size);
  fclose(l_file);
  return JDT_RS_OK;
}

/**
 * Read file and return any data type
 *
 * Be aware! This function read only one data type and return it
 * so for list of some structures will return only one entity,
 * make structure as root
 *
 * @param p_file_path File path with its file name and extension, e.g. data.dat
 * @param p_data_size Size of some data, e.g sizeof(my_struct)
 * @return Return any data type
 */
static void *jdt_file_read(const char *p_file_path, size_t p_data_size) {
  FILE *l_file = fopen(p_file_path, "r");
  if (l_file == NULL) {
    JDT_LOG_ERROR("Failed to open file [file_path=%s]!", p_file_path);
    return NULL;
  }

  void *l_data = malloc(p_data_size);
  size_t l_status = fread(l_data, p_data_size, 1, l_file);
  if (l_status == 0) {
    JDT_LOG_ERROR(
      "Failed to read data from file [file_path=%s; data_size=%ul]",
      p_file_path, p_data_size);

    fclose(l_file);
    free(l_data);
    return NULL;
  }

  fclose(l_file);
  return l_data;
}

// =====================================================================================================================
//                                              Data type conversions
// =====================================================================================================================
// Data type conversions. For example conversion string to number like integer or getting specific bit from integer.
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Convert integer with user defined base to String.
 *
 * Source: https://www.strudel.org.uk/itoa/
 *
 * @param p_number Number, e.g. 5, 6, 20, 100, ...
 * @param p_base Base number, e.g. 10, 16 (HEX), ...
 * @return
 */
static inline char *jdt_data_int_to_str(int p_number, int p_base) {
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

/**
 * Get specific bit from integer value at specific bit position.
 *
 * @param l_data Value from which will be extracted specific bit
 * @param l_pos Position of specific bit
 * @return Return bit from l_data
 */
static inline u8 jdt_data_get_bit(u32 l_data, u32 l_pos) {
  return (l_data >> l_pos) & 1;
}

// =====================================================================================================================
//                                              Mathematical functions
// =====================================================================================================================
// Mathematical function and randomizing algorithms.
// ---------------------------------------------------------------------------------------------------------------------

static const f32 JDT_MATH_PI = 3.14159f;
static const f32 JDT_MATH_2PI = 6.28318f;

/**
 * Squirrel3
 * Link: https://www.youtube.com/watch?v=LWFzPP8ZbdU
 */
static u32 jdt_math_squirrel3(u32 p_index, u32 p_seed) {
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

static s8 jdt_math_abs_s8(s8 p_value) {
  if (p_value < 0) {
    return p_value *= -1;
  } else {
    return p_value;
  }
}

static s16 jdt_math_abs_s16(s16 p_value) {
  if (p_value < 0) {
    return p_value *= -1;
  } else {
    return p_value;
  }
}

static s32 jdt_math_abs_s32(s32 p_value) {
  if (p_value < 0) {
    return p_value *= -1;
  } else {
    return p_value;
  }
}

static s64 jdt_math_abs_s64(s64 p_value) {
  if (p_value < 0) {
    return p_value *= -1;
  } else {
    return p_value;
  }
}

static s8 jdt_math_min_s8(s8 p_value, s8 p_min) {
  if (p_value < p_min) {
    return p_min;
  } else {
    return p_value;
  }
}

static s16 jdt_math_min_s16(s16 p_value, s16 p_min) {
  if (p_value < p_min) {
    return p_min;
  } else {
    return p_value;
  }
}

static s32 jdt_math_min_s32(s32 p_value, s32 p_min) {
  if (p_value < p_min) {
    return p_min;
  } else {
    return p_value;
  }
}

static s64 jdt_math_min_s64(s64 p_value, s64 p_min) {
  if (p_value < p_min) {
    return p_min;
  } else {
    return p_value;
  }
}

static s8 jdt_math_max_s8(s8 p_value, s8 p_max) {
  if (p_value > p_max) {
    return p_max;
  } else {
    return p_value;
  }
}

static s16 jdt_math_max_s16(s16 p_value, s16 p_max) {
  if (p_value > p_max) {
    return p_max;
  } else {
    return p_value;
  }
}

static s32 jdt_math_max_s32(s32 p_value, s32 p_max) {
  if (p_value > p_max) {
    return p_max;
  } else {
    return p_value;
  }
}

static s64 jdt_math_max_s64(s64 p_value, s64 p_max) {
  if (p_value > p_max) {
    return p_max;
  } else {
    return p_value;
  }
}

static s8 jdt_math_clamp_s8(s8 p_value, s8 p_min, s8 p_max) {
  if (p_value < p_min) {
    return p_min;
  }
  if (p_value > p_max) {
    return p_max;
  }
  return p_value;
}

static s16 jdt_math_clamp_s16(s16 p_value, s16 p_min, s16 p_max) {
  if (p_value < p_min) {
    return p_min;
  }
  if (p_value > p_max) {
    return p_max;
  }
  return p_value;
}

static s32 jdt_math_clamp_s32(s32 p_value, s32 p_min, s32 p_max) {
  if (p_value < p_min) {
    return p_min;
  }
  if (p_value > p_max) {
    return p_max;
  }
  return p_value;
}

static s64 jdt_math_clamp_s64(s64 p_value, s64 p_min, s64 p_max) {
  if (p_value < p_min) {
    return p_min;
  }
  if (p_value > p_max) {
    return p_max;
  }
  return p_value;
}

// =====================================================================================================================
//                                                Asset operator
// =====================================================================================================================
// Asset creator and reader, e.g create font assets from header file or parser font assets from custom data.
// ---------------------------------------------------------------------------------------------------------------------

typedef struct {
  u8 data[256][8];
} jdt_term_asset_t;

static jdt_term_asset_t *jdt_asset_read(char *p_path) {
  return jdt_file_read(p_path, sizeof(jdt_term_asset_t));
}

static u8 jdt_asset_create(char *p_path, size_t p_size, size_t p_height, const u8 p_bitmap[p_size][p_height]) {
  jdt_term_asset_t l_asset;
  for (int x = 0; x < p_size; ++x) {
    for (int y = 0; y < p_height; ++y) {
      l_asset.data[x][y] = p_bitmap[x][y];
    }
  }
  JDT_LOG_DEBUG("Saving assets [path=%s; size=[%d; %d]]", p_path, p_size, p_height);
  jdt_file_write(p_path, &l_asset, sizeof(jdt_term_asset_t));
}

#endif //JADEITITE_FRAMEWORK_H
