#ifndef SHIFT_H
#define SHIFT_H

#include <stdint.h>
#include <stddef.h>
#include <uchar.h>

#if defined(__GNUC__) || defined(__clang__)
    #define LIKELY(x)   __builtin_expect(!!(x), 1)
    #define UNLIKELY(x) __builtin_expect(!!(x), 0)
    #define FORCE_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
    #define LIKELY(x)   (x)
    #define UNLIKELY(x) (x)
    #define FORCE_INLINE __forceinline
#else
    #define LIKELY(x)   (x)
    #define UNLIKELY(x) (x)
    #define FORCE_INLINE inline
#endif

#define SHIFT_OP_NONE   0x00
#define SHIFT_OP_LSHIFT 0x01
#define SHIFT_OP_RSHIFT 0x02
#define SHIFT_OP_AND    0x03
#define SHIFT_OP_OR     0x04
#define SHIFT_OP_XOR    0x05

#define SHIFT_TYPE_U8    8
#define SHIFT_TYPE_U16   16
#define SHIFT_TYPE_U32   32
#define SHIFT_TYPE_I8   -8
#define SHIFT_TYPE_I16  -16
#define SHIFT_TYPE_I32  -32

#define FLAG_OPCODE_MASK 0x000000FF
#define FLAG_TYPE_MASK   0x0000FF00
#define FLAG_TYPE_SHIFT  8
#define FLAG_VALID       0x00010000

typedef union {
    uint8_t  u8;
    uint16_t u16;
    uint32_t u32;
    int8_t   i8;
    int16_t  i16;
    int32_t  i32;
} shift_val_t;

typedef struct shift_node {
    uint32_t            flags; // Tracks operational flags and internal state
    uint32_t            op_arg;
    shift_val_t         target_val;
    struct shift_node   *next;
} shift_node_t;

typedef struct {
    shift_node_t *head;
    shift_node_t *tail;
    shift_node_t *free_head;
} shift_pipeline_t;

typedef struct {
    const char32_t   *raw_cmd;
    shift_pipeline_t *pipeline;
    char32_t         *output_buf;
    char32_t         *error_buf;
} shift_ctx_t;

int32_t shift_parse_pipeline(shift_ctx_t *ctx);

#endif
