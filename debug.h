/**
 * @file debug.h
 * @author vincent.vdb@gmail.com
 * @brief printing in debug mode
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef NDEBUG
#define debug_print(fmt, ...) \
        do { fprintf(stderr, "%s() [l.%d]: " fmt, \
                                __func__, __LINE__, ##__VA_ARGS__); } while (0)
#else
#define debug_print(fmt, ...) do {} while (0)
#endif