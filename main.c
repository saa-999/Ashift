#include <stdio.h>
#include <stdlib.h>
#include "shift.h"

static FORCE_INLINE uint8_t extract_opcode(uint32_t flags) {
    return (uint8_t)(flags & FLAG_OPCODE_MASK);
}

static FORCE_INLINE int8_t extract_type(uint32_t flags) {
    return (int8_t)((flags & FLAG_TYPE_MASK) >> FLAG_TYPE_SHIFT);
}

static FORCE_INLINE void print_str(const char *str) {
    while (*str) {
        putchar(*str++);
    }
}

static FORCE_INLINE void print_u32(uint32_t val) {
    if (val == 0) {
        putchar('0');
        return;
    }
    char buf[12];
    int idx = 0;
    while (val > 0) {
        buf[idx++] = '0' + (val % 10);
        val /= 10;
    }
    while (idx > 0) {
        putchar(buf[--idx]);
    }
}

static FORCE_INLINE void print_binary_blocks(uint32_t val, int8_t type_size) {
    uint8_t bits = (type_size < 0) ? -type_size : type_size;
    for (int i = bits - 1; i >= 0; i--) {
        if ((i & 7) == 7) {
            putchar('['); putchar(' ');
        }
        putchar(((val >> i) & 1) ? '1' : '0');
        if ((i & 7) == 0) {
            putchar(' '); putchar(']'); putchar(' ');
        }
    }
    putchar('\n');
}

static FORCE_INLINE uint32_t get_raw_value(shift_node_t *node, int8_t data_type) {
    switch (data_type) {
        case SHIFT_TYPE_U8:  return node->target_val.u8;
        case SHIFT_TYPE_I8:  return (uint8_t)node->target_val.i8;
        case SHIFT_TYPE_U16: return node->target_val.u16;
        case SHIFT_TYPE_I16: return (uint16_t)node->target_val.i16;
        case SHIFT_TYPE_U32: return node->target_val.u32;
        case SHIFT_TYPE_I32: return (uint32_t)node->target_val.i32;
        default: return 0;
    }
}

static FORCE_INLINE void print_type_name(int8_t type_size) {
    switch (type_size) {
        case SHIFT_TYPE_U8:  print_str("u8 "); break;
        case SHIFT_TYPE_I8:  print_str("i8 "); break;
        case SHIFT_TYPE_U16: print_str("u16"); break;
        case SHIFT_TYPE_I16: print_str("i16"); break;
        case SHIFT_TYPE_U32: print_str("u32"); break;
        case SHIFT_TYPE_I32: print_str("i32"); break;
        default: print_str("UNK"); break;
    }
}

static void print_help() {

    print_str("Usage: shift \"[op] <type> <value>\"\n\n");
    print_str("Options:\n");
    print_str("  -h, --help    Show this highly optimized help screen.\n\n");
    print_str("Operations:\n");
    print_str("  <<            Left Shift\n");
    print_str("  >>            Right Shift\n");
    print_str("  -n            Bitwise AND\n");
    print_str("  -o            Bitwise OR\n");
    print_str("  -x            Bitwise XOR\n");
    print_str("  ~             Bitwise NOT\n\n");
    print_str("Data Types:\n");
    print_str("  u8, i8, u16, i16, u32, i32\n\n");
    print_str("Examples:\n");
    print_str("  shift \"<< 2 u32 100\"   Left shift 100 by 2 as a u32.\n");
    print_str("  shift \">> 3 i8 100\"    Right shift 100 by 3 as an i8.\n");
    print_str("  shift \"~ u32 (10+20)\"  Compound expressions and bitwise NOT.\n");
    print_str("======================================================\n\n");
}

int main(int argc, char *argv[]) {
    if (UNLIKELY(argc < 2)) {
        print_str("Error: Missing arguments.\n");
        print_str("Usage: shift \"[op] <type> <value>\"\n");
        return 1;
    }

    if (UNLIKELY(argv[1][0] == '-' && (argv[1][1] == 'h' || (argv[1][1] == '-' && argv[1][2] == 'h')))) {
        print_help();
        return 0;
    }

    char raw_input[256] = {0};
    int input_len = 0;
    for (int i = 1; i < argc && input_len < 200; i++) {
        char *ptr = argv[i];
        while (*ptr && input_len < 200) {
            raw_input[input_len++] = *ptr++;
        }
        raw_input[input_len++] = ' ';
    }
    raw_input[input_len] = '\0';

    char32_t cmd_buffer[256] = {0};
    for (int i = 0; i < input_len; i++) {
        cmd_buffer[i] = (char32_t)raw_input[i];
    }

    shift_node_t nodes_pool[10] = {0};
    for (int i = 0; i < 9; i++) {
        nodes_pool[i].next = &nodes_pool[i + 1];
    }

    shift_pipeline_t pipeline = {
        .head = NULL,
        .tail = NULL,
        .free_head = &nodes_pool[0]
    };

    shift_ctx_t ctx = {
        .raw_cmd = cmd_buffer,
        .pipeline = &pipeline,
        .output_buf = NULL,
        .error_buf = NULL
    };

    int32_t status = shift_parse_pipeline(&ctx);

    if (UNLIKELY(status != 0)) {
        print_str("\n[!] Architecture Error: Parsing failed.\n");
        return 1;
    }


    shift_node_t *current = pipeline.head;
    int instruction_count = 1;

    while (current != NULL) {
        if (UNLIKELY(!(current->flags & FLAG_VALID))) break;
        print_str("\n[ Instruction "); print_u32(instruction_count++); print_str(" ]\n");
        
        int8_t data_type = extract_type(current->flags);
        uint8_t opcode = extract_opcode(current->flags);
        
        print_str("Data Type   : ");
        print_type_name(data_type);
        print_str("\n");

        uint32_t raw_val = get_raw_value(current, data_type);

        if (UNLIKELY(opcode == SHIFT_OP_NONE)) {
            print_str("Mode        : [ DISPLAY ONLY ]\n");
            print_str("Value       : "); print_u32(raw_val); print_str("\n");
            print_str("Mem Block   : "); print_binary_blocks(raw_val, data_type);
        } else {
            print_str("Mode        : [ OPERATION DETECTED: "); print_u32(opcode); print_str(" ]\n");
            print_str("Value (Raw) : "); print_u32(raw_val); print_str("\n");
            print_str("Target Arg  : "); print_u32(current->op_arg); print_str("\n");
            print_str("Base Block  : "); print_binary_blocks(raw_val, data_type);
            
            if (LIKELY(opcode != SHIFT_OP_NONE)) {
                uint32_t shifted_val = 0;
                
                if (opcode == SHIFT_OP_LSHIFT) {
                    print_str("Direction   : Left (<<)\n");
                    shifted_val = raw_val << current->op_arg;
                } else if (opcode == SHIFT_OP_RSHIFT) {
                    print_str("Direction   : Right (>>)\n");
                    switch (data_type) {
                        case SHIFT_TYPE_I8:  shifted_val = (uint8_t)((int8_t)raw_val >> current->op_arg); break;
                        case SHIFT_TYPE_I16: shifted_val = (uint16_t)((int16_t)raw_val >> current->op_arg); break;
                        case SHIFT_TYPE_I32: shifted_val = (uint32_t)((int32_t)raw_val >> current->op_arg); break;
                        case SHIFT_TYPE_U8:  shifted_val = (uint8_t)((uint8_t)raw_val >> current->op_arg); break;
                        case SHIFT_TYPE_U16: shifted_val = (uint16_t)((uint16_t)raw_val >> current->op_arg); break;
                        case SHIFT_TYPE_U32: shifted_val = (uint32_t)raw_val >> current->op_arg; break;
                        default: shifted_val = raw_val >> current->op_arg; break;
                    }
                } else if (opcode == SHIFT_OP_NOT) {
                    print_str("Direction   : NOT (~)\n");
                    shifted_val = ~raw_val;
                } else if (opcode == SHIFT_OP_AND) {
                    print_str("Direction   : AND (&)\n");
                    shifted_val = raw_val & current->op_arg;
                } else if (opcode == SHIFT_OP_OR) {
                    print_str("Direction   : OR (|)\n");
                    shifted_val = raw_val | current->op_arg;
                } else if (opcode == SHIFT_OP_XOR) {
                    print_str("Direction   : XOR (^)\n");
                    shifted_val = raw_val ^ current->op_arg;
                }
                
                uint8_t bits = (data_type < 0) ? -data_type : data_type;
                if (bits < 32) {
                    shifted_val &= ((1U << bits) - 1);
                }
                
                print_str("Orig Value  : "); print_u32(raw_val); print_str("\n");
                print_str("New Value   : "); print_u32(shifted_val); print_str("\n");
                print_str("Result Block: "); print_binary_blocks(shifted_val, data_type);
            }
        }

        current = current->next;
    }

    print_str("\n======================================================\n\n");
    return 0;
}
