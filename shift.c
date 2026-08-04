#include "shift.h"

#define SKIP_WHITESPACE(ptr) while (*(ptr) == ' ' || *(ptr) == '\t') { (ptr)++; }
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')

static FORCE_INLINE uint32_t parse_unsigned_int(const char32_t **stream) {
    const char32_t *ptr = *stream;
    uint32_t val = 0;

    if (ptr[0] == '0' && (ptr[1] == 'x' || ptr[1] == 'X')) {
        ptr += 2;
        while (1) {
            if (LIKELY(*ptr >= '0' && *ptr <= '9')) {
                val = (val << 4) | (*ptr - '0');
            } else if (*ptr >= 'a' && *ptr <= 'f') {
                val = (val << 4) | (*ptr - 'a' + 10);
            } else if (*ptr >= 'A' && *ptr <= 'F') {
                val = (val << 4) | (*ptr - 'A' + 10);
            } else {
                break;
            }
            ptr++;
        }
    } else {
        while (LIKELY(IS_DIGIT(*ptr))) {
            val = (val << 3) + (val << 1) + (*ptr - '0');
            ptr++;
        }
    }

    *stream = ptr;
    return val;
}


static FORCE_INLINE int8_t parse_type_descriptor(const char32_t **stream) {
    const char32_t *ptr = *stream;
    int8_t type_flag = 0;

    if (ptr[0] == 'u') {
        if (ptr[1] == '3' && ptr[2] == '2') {
        type_flag = SHIFT_TYPE_U32;
        ptr += 3;
        }
        else if (ptr[1] == '1' && ptr[2] == '6')
        { type_flag = SHIFT_TYPE_U16;
        ptr += 3;
        } else if (ptr[1] == '8') {
        type_flag = SHIFT_TYPE_U8;
        ptr += 2;
        }
    }
    else if (ptr[0] == 'i') {
        if (ptr[1] == '3' && ptr[2] == '2') {
        type_flag = SHIFT_TYPE_I32;
        ptr += 3;
        }
        else if (ptr[1] == '1' && ptr[2] == '6') {
        type_flag = SHIFT_TYPE_I16;
        ptr += 3;
        }
        else if (ptr[1] == '8') {
        type_flag = SHIFT_TYPE_I8;
        ptr += 2; }
    }

    if (type_flag != 0) {
        *stream = ptr;
    }
    return type_flag;
}

static FORCE_INLINE uint8_t parse_opcode(const char32_t **stream) {
    const char32_t *ptr = *stream;
    uint8_t opcode = SHIFT_OP_NONE;

    if (LIKELY(*ptr == '<' && *(ptr + 1) == '<')) {
        opcode = SHIFT_OP_LSHIFT;
        ptr += 2;
        *stream = ptr;
        return opcode;
    } else if (LIKELY(*ptr == '>' && *(ptr + 1) == '>')) {
        opcode = SHIFT_OP_RSHIFT;
        ptr += 2;
        *stream = ptr;
        return opcode;
    }

    if (UNLIKELY(*ptr == '-')) {
        ptr++;
        switch (*ptr) {
            case 'f': opcode = SHIFT_OP_LSHIFT; break;
            case 'n': opcode = SHIFT_OP_AND; break;
            case 'o': opcode = SHIFT_OP_OR; break;
            case 'x': opcode = SHIFT_OP_XOR; break;
            default: return SHIFT_OP_NONE;
        }
        ptr++;
        *stream = ptr;
    }
    return opcode;
}

static FORCE_INLINE shift_node_t* alloc_pipeline_node(shift_pipeline_t *pipeline) {
    if (pipeline == NULL || pipeline->free_head == NULL) {
        return NULL;
    }
    shift_node_t *node = pipeline->free_head;
    pipeline->free_head = node->next;
    node->next = NULL;
    return node;
}

static FORCE_INLINE void append_pipeline_node(shift_pipeline_t *pipeline, shift_node_t *node) {
    if (pipeline->head == NULL) {
        pipeline->head = node;
        pipeline->tail = node;
    } else {
        pipeline->tail->next = node;
        pipeline->tail = node;
    }
}

int32_t shift_parse_pipeline(shift_ctx_t *ctx) {
    if (ctx == NULL || ctx->raw_cmd == NULL || ctx->pipeline == NULL) {
        return -1;
    }

    const char32_t *cursor = ctx->raw_cmd;

    while (*cursor != '\0') {
        SKIP_WHITESPACE(cursor);
        if (*cursor == '\0') break;

        uint8_t opcode = parse_opcode(&cursor);

        SKIP_WHITESPACE(cursor);
        uint32_t op_arg = parse_unsigned_int(&cursor);

        SKIP_WHITESPACE(cursor);

        int8_t data_type = parse_type_descriptor(&cursor);
        if (data_type == 0) return -1;

        SKIP_WHITESPACE(cursor);

        uint32_t raw_val = parse_unsigned_int(&cursor);

        shift_node_t *node = alloc_pipeline_node(ctx->pipeline);
        if (node == NULL) return -2;

        node->flags = (opcode & FLAG_OPCODE_MASK) | 
                      (((uint32_t)(uint8_t)data_type << FLAG_TYPE_SHIFT) & FLAG_TYPE_MASK) | 
                      FLAG_VALID;
        node->op_arg = op_arg;

        switch (data_type) {
            case SHIFT_TYPE_U8:  node->target_val.u8  = (uint8_t)raw_val;  break;
            case SHIFT_TYPE_U16: node->target_val.u16 = (uint16_t)raw_val; break;
            case SHIFT_TYPE_U32: node->target_val.u32 = raw_val;           break;
            case SHIFT_TYPE_I8:  node->target_val.i8  = (int8_t)raw_val;   break;
            case SHIFT_TYPE_I16: node->target_val.i16 = (int16_t)raw_val;  break;
            case SHIFT_TYPE_I32: node->target_val.i32 = (int32_t)raw_val;  break;
        }

        append_pipeline_node(ctx->pipeline, node);

        SKIP_WHITESPACE(cursor);

        if (*cursor == '&') {
            cursor++;
            continue;
        } else if (*cursor == '\0') {
            break;
        } else {
            return -1;
        }
    }

    return 0;
}
