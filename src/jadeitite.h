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
#define JADEITITE_VER_MINOR 4
#define JADEITITE_VER_PATCH 0

// Framework version date YYYY-MM-DD
#define JADEITITE_VER_DATE 20221029

// =====================================================================================================================
//                                                    Logging
// =====================================================================================================================
// Lightweight logging framework with source linking and precision time.
//
// Examples:
//  LOG_INFO("This is my value %d", 123);
//  LOG_ERROR("This went wrong! [value=%x; error=%s]", error.value, error.message);
// ---------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

typedef enum {
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
    LOG_LEVEL_DEBUG
} log_level;

// src: https://stackoverflow.com/a/27678121
static void log_logTime(void) {
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

static void log_logSrc(const char *p_file, int p_line) {
    printf("[ %s:%d ]", p_file, p_line);
}

static void log_logLevel(log_level p_level) {
    switch (p_level) {
        case LOG_LEVEL_INFO:printf("[INFO]: ");
            break;
        case LOG_LEVEL_WARN:printf("[WARN]: ");
            break;
        case LOG_LEVEL_ERROR:printf("[ERROR]: ");
            break;
        case LOG_LEVEL_FATAL:printf("[FATAL]: ");
            break;
        case LOG_LEVEL_DEBUG:printf("[DEBUG]: ");
            break;
        default:printf("Undefined behaviour!\n");
            return;
    }
}

static void log_log(
        log_level p_level,
        const char *p_file,
        int p_line,
        const char *p_input,
        ...
) {
    log_logTime();
    log_logSrc(p_file, p_line);
    log_logLevel(p_level);
    va_list l_argList;
    va_start(l_argList, p_input);
    vprintf(p_input, l_argList);
    va_end(l_argList);
    printf("\n");
}

#define GET_SRC_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_INFO(...) log_log(LOG_LEVEL_INFO, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_WARN(...) log_log(LOG_LEVEL_WARN, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_log(LOG_LEVEL_ERROR, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_log(LOG_LEVEL_FATAL, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) log_log(LOG_LEVEL_DEBUG, GET_SRC_FILENAME , __LINE__, __VA_ARGS__)

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

#define RS_OK     0
#define RS_FAILED 1

// =====================================================================================================================
//                                               Memory operators
// =====================================================================================================================
// Memory operation for custom memory allocating.
//
// This memory operators is meant to be just as fun.
// ---------------------------------------------------------------------------------------------------------------------

#include <stdlib.h>

typedef struct mem_block_u16_rt {
    u16 start, end;
    void *data;
    struct mem_block_u16_rt *next;
} mem_block_u16_t;

mem_block_u16_t *mem_u16_init(u16 p_max_size) {
    mem_block_u16_t *l_block = malloc(sizeof (mem_block_u16_t));
    l_block->next = NULL;
    l_block->data = NULL;
    l_block->start = 0;
    l_block->end = p_max_size;

    return l_block;
}

void *mem_u16_alloc(
        mem_block_u16_t *p_mem_block,
        u16 p_size
) {
    const int l_calc = p_mem_block->start + p_size <= p_mem_block->end;
    if (p_mem_block->next == NULL && p_mem_block->data == NULL && l_calc) {
        mem_block_u16_t *l_block = malloc(sizeof(mem_block_u16_t));
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
        return mem_u16_alloc(p_mem_block->next, p_size);
    } else {
        return NULL;
    }
}

void mem_u16_free(mem_block_u16_t *p_mem_block) {
    if (p_mem_block->next == NULL) {
        if (p_mem_block->data != NULL) {
            free(p_mem_block->data);
        }
    } else {
        mem_u16_free(p_mem_block->next);
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
 * @return Return RS_OK if write operation is successful, otherwise return RS_FAILED
 */
u8 file_write(const char *p_file_path, void *p_data, size_t p_data_size) {
    FILE* l_file = fopen(p_file_path, "w");
    if (l_file == NULL) {
        LOG_ERROR("Failed to open file [file_path=%s]!", p_file_path);
        return RS_FAILED;
    }

    size_t l_status = fwrite(p_data, p_data_size, 1, l_file);
    if (l_status == 0) {
        LOG_ERROR(
                "Failed to write data to file [file_path=%s; data_size=%ul]",
                p_file_path, p_data_size);

        fclose(l_file);
        return RS_FAILED;
    }

    fclose(l_file);
    return RS_OK;
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
void *file_read(const char *p_file_path, size_t p_data_size) {
    FILE* l_file = fopen(p_file_path, "r");
    if (l_file == NULL) {
        LOG_ERROR("Failed to open file [file_path=%s]!", p_file_path);
        return NULL;
    }

    void *l_data = malloc(p_data_size);
    size_t l_status = fread(l_data, p_data_size, 1, l_file);
    if (l_status == 0) {
        LOG_ERROR(
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
static inline char *int_to_str(int p_number, int p_base) {
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
static inline u8 get_bit(u32 l_data, u32 l_pos) {
    return (l_data >> l_pos) & 1;
}

// =====================================================================================================================
//                                              Mathematical functions
// =====================================================================================================================
// Mathematical function and randomizing algorithms.
// ---------------------------------------------------------------------------------------------------------------------

static const f32 s_pi  = 3.14159f;
static const f32 s_2pi = 6.28318f;

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

// =====================================================================================================================
//                                          SDL2 with Window and Renderer
// =====================================================================================================================
// SDL2 with Window and Renderer implementation for applications.
// ---------------------------------------------------------------------------------------------------------------------

#include <SDL2/SDL.h>

static SDL_Window *s_sdl_window;
static SDL_Renderer *s_sdl_renderer;

/**
 * Callbacks structure contain all necessary callback for functional OpenGl.
 * Used for setting up callback for Jadeitite framework
 *
 * @struct onUpdate(void) - Called every frame. Used for drawing and other update event.
 * @struct onKeyboardDown(unsigned char, int, int) - Called on any key down.
 * @struct onKeyboardUp(unsigned char, int, int) - Called on any key up.
 * @struct onAttach(int, char **) - Called after initialized Amber framework and OpenGl.
 * @struct onDetach(int, char **) - Called on close/end.
 */
typedef struct {
    void (*onUpdate)(void);
    void (*onKeyboardDown)(unsigned char, int, int);
    void (*onKeyboardUp)(unsigned char, int, int);
    void (*onAttach)(int, char **);
    void (*onDetach)(int, char **);
    void (*onResize)(int, int);
} callbacks_t;

/**
 * Window properties structure contain all necessary variables for initialize window with OpenGl/Glut.
 *
 * @struct width - Window width/X.
 * @struct height - Window height/Y.
 * @struct label - Window name/label.
 * @struct autoRefresh - If is true then enable auto refreshing window
 */
typedef struct {
    int width;
    int height;
    const char *label;
    int autoRefresh;
    unsigned char renderMultiplier;
} winProp_t;

/**
 * Clear window
 */
static inline void render_begin(void) {
    SDL_RenderClear(s_sdl_renderer);
}

/**
 * Swap render buffer
 */
static inline void render_end(void) {
    SDL_RenderPresent(s_sdl_renderer);
}

u8 window_close() {
    SDL_DestroyRenderer(s_sdl_renderer);
    SDL_DestroyWindow(s_sdl_window);

    return RS_OK;
}

u8 window_init(int p_argc, char *p_argv[], winProp_t p_winProp) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        LOG_FATAL("Failed to initialize sdl video [error=%s]", SDL_GetError());
        return RS_FAILED;
    }

    s_sdl_window = SDL_CreateWindow(
            p_winProp.label,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            p_winProp.width,
            p_winProp.height,
            0
    );
    if (s_sdl_window == NULL) {
        LOG_FATAL("Failed to create sdl window [error=%s]", SDL_GetError());
        return RS_FAILED;
    }

    s_sdl_renderer = SDL_CreateRenderer(s_sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (s_sdl_renderer == NULL) {
        LOG_FATAL("Failed to create sdl renderer [error=%s]", SDL_GetError());
        return RS_FAILED;
    }

    SDL_SetRenderDrawColor(s_sdl_renderer, 0, 0, 0, 255);

    LOG_DEBUG("SDL2 Window initialize successfully");
    return RS_OK;
}

u8 window_run(callbacks_t p_callbacks, winProp_t p_winProp) {
    bool l_running = 1;
    while (l_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:{
                    l_running = 0;
                    break;
                }

                default:break;
            }
        }
        p_callbacks.onUpdate;
    }
    p_callbacks.onDetach;
    window_close();
    return RS_OK;
}

// =====================================================================================================================
//                                               EntryPoint
// =====================================================================================================================
// Main entrypoint for Jadeitite library. Main function is implemented HERE.
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Function for setting up callbacks and window properties for APP.
 *
 * @param p_callbacks Callbacks function
 * @param p_winProp Windows properties
 * @param p_argc Argument count
 * @param p_argv Argument list
 *
 * @return Return error code, 0 as PASSED, otherwise as FAILED
 *
 * @see t_callbacks
 */
extern int setup(
        callbacks_t *p_callbacks,
        winProp_t *p_winProp,
        int p_argc,
        char *p_argv[]
);

int main(int argc, char *argv[]) {
    LOG_INFO(
            "Jadeitite framework - [%d.%d.%d - %d]",
            JADEITITE_VER_MAJOR,
            JADEITITE_VER_MINOR,
            JADEITITE_VER_PATCH,
            JADEITITE_VER_DATE
    );

    callbacks_t l_callbacks;
    winProp_t l_windProp;

    int l_setup = setup(&l_callbacks, &l_windProp, argc, argv);

    if (l_setup) {
        window_init(argc, argv, l_windProp);
        l_callbacks.onAttach(argc, argv);
        window_run(l_callbacks, l_windProp);
        l_callbacks.onDetach(argc, argv);
    }

    LOG_INFO("Closing Jadeitite framework");
    return 0;
}

#endif //JADEITITE_FRAMEWORK_H
