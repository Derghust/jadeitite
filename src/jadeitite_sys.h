#ifndef JADEITITE_SYS_H
#define JADEITITE_SYS_H

// link: https://stackoverflow.com/questions/1505582/determining-32-vs-64-bit-in-c
// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define SYS64
typedef unsigned long size_t;
#else
#define SYS32
typedef unsigned int size_t;
#endif
#endif

// link: https://stackoverflow.com/questions/1505582/determining-32-vs-64-bit-in-c
// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define SYS64
typedef unsigned long size_t;
#else
#define SYS32
typedef unsigned int size_t;
#endif
#endif

#endif //JADEITITE_SYS_H
