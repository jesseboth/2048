    .data

clear:      .string 27, "[0m", 27, "[?25l", 27, "[2J", 27, "[0;0;H", 0
;* clear:      .string 27, "[0m", 27, "[?25h", 27, "[2J", 27, "[0;0;H", 0


top_left:   .string 27, "[5;26;H", 0

center:     .string 0xA, 0xA, 0xA, 0
boarder:    .string 9,9,9,27, "[37;40;1m+------+------+------+------+", 0xA, 0xD
            .string 9,9,9,27, "[37;40;1m|      |      |      |      |", 0xA, 0xD
            .string 9,9,9,27, "[37;40;1m|      |      |      |      |", 0xA, 0xD
            .string 9,9,9,27, "[37;40;1m|      |      |      |      |", 0xA, 0xD, 0

bottom:     .string 9,9,9,27, "[37;40;1m+------+------+------+------+", 0xA, 0xD, 0

colors:     .string 27, "[0m",0,0,0,0,0,0,0,0,0,0,0
            .string 27, "[30;48;5;117m", 0
            .string 27, "[30;48;5;153m", 0
            .string 27, "[30;48;5;189m", 0
            .string 27, "[30;48;5;225m", 0
            .string 27, "[30;48;5;224m", 0
            .string 27, "[30;48;5;223m", 0
            .string 27, "[30;48;5;222m", 0
            .string 27, "[30;48;5;221m", 0
            .string 27, "[30;48;5;220m", 0
            .string 27, "[30;48;5;215m", 0
            .string 27, "[30;48;5;214m", 0
            .string 27, "[30;48;5;197m", 0


square:     .string "      ", 0xA, 27, "[6D"
            .string "      ", 0xA, 27, "[6D"
            .string "      ", 0

reset:      .string 27, "[0m", 0

square_val: .string 27, "[30;1m"
square_num: .string "0000", 0

square_down:    .string 27, "[4B", 0
square_right:   .string 27, "[7C", 0
cursor_up:      .string 27, "[1A", 0
cursor_left:    .string 27, "[#D", 0

;* subboard:   .char 0x0, 0x0, 0x0, 0x0
;*             .char 0x0, 0x0, 0x0, 0x0
;*             .char 0x0, 0x0, 0x0, 0x0
;*             .char 0x0, 0x0, 0x0, 0x0
subboard:   .char 0x2, 0x3, 0x3, 0x0
            .char 0x1, 0x3, 0x4, 0x0
            .char 0x1, 0x0, 0x0, 0x4
            .char 0x1, 0x1, 0x5, 0x0

score:          .int 0
score_string:   .space 16


    .text
    .global output_boarder
    .global place_square
    .global draw_board
    .global clear_board
    .global shift_right_wrapper
    .global shift_left_wrapper
    .global shift_down_wrapper
    .global shift_up_wrapper


    .global output_string
    .global str2int
    .global int2str

    .export shift_right_op
    .export shift_left_op
    .export shift_down_op
    .export shift_up_op

    .export LCD_setCursor
    .export LCD_print

ptr_to_clear:   .word clear 
ptr_to_top_left:.word top_left
ptr_to_center:  .word center
ptr_to_boarder: .word boarder
ptr_to_bottom: .word bottom
ptr_to_colors: .word colors
ptr_to_reset:  .word reset
ptr_to_square: .word square
ptr_to_square_num:  .word square_num
ptr_to_square_val:  .word square_val


ptr_to_square_down: .word square_down
ptr_to_square_right: .word square_right
ptr_to_cursor_up:   .word cursor_up
ptr_to_cursor_left:   .word cursor_left

ptr_to_subboard:    .word subboard

ptr_to_score:       .word score
ptr_to_score_string:.word score_string

SQUARE_WIDTH:   .equ 6
SQUARE_HEIGHT:  .equ 3 
SQUARE_CENTER:  .equ 3
SQUARE_OFFSET:  .equ 15

output_boarder:
	STMFD SP!,{lr, r4-r11}

    ldr r0, ptr_to_clear
    bl output_string
    ldr r0, ptr_to_center
    bl output_string

    ldr r0, ptr_to_boarder
    bl output_string

    ldr r0, ptr_to_boarder
    bl output_string
    
    ldr r0, ptr_to_boarder
    bl output_string
    
    ldr r0, ptr_to_boarder
    bl output_string

    ldr r0, ptr_to_bottom
    bl output_string

	LDMFD sp!, {lr, r4-r11}
	mov pc, lr

;* place square in position
;* input - r0 (x coord)
;*       - r1 (y coord)
;*       - r2 (shift amount)
; * output
place_square:
	STMFD SP!,{lr, r4-r11}

    ;* save inputs
    mov r4, r0
    mov r5, r1
    mov r6, r2

    mov r1, #SQUARE_OFFSET
    mul r1, r1, r2
    ldr r0, ptr_to_colors
    add r0, r0, r1
    bl output_string

    ;* move cursor to to left
    ldr r0, ptr_to_top_left
    bl output_string

    cmp r4, #0
    beq _square_down_check


_square_right:
    ldr r0, ptr_to_square_right
    bl output_string

    sub r4, r4, #1
    cmp r4, #0
    bne _square_right

_square_down_check:
    cmp r5, #0
    beq _square_out

_square_down:
    ldr r0, ptr_to_square_down
    bl output_string

    sub r5, r5, #1
    cmp r5, #0
    bne _square_down


_square_out:

    ldr r0, ptr_to_square
    bl output_string

    cmp r6, #0
    beq _exit_place_square


    ldr r0, ptr_to_cursor_up
    bl output_string

    mov r0, #1
    mov r1, r6
    lsl r0, r0, r1
    ldr r1, ptr_to_square_num
    bl int2str
    

    cmp r1, #3
    ;* bgt _square_4_chars
    bge _square_3_chars

_square_2_chars:
    ldr r0, ptr_to_cursor_left
    mov r1, #0x34
    strb r1, [r0, #2]
    bl output_string

    b _print_val
_square_3_chars:
    ldr r0, ptr_to_cursor_left
    mov r1, #0x35
    strb r1, [r0, #2]
    bl output_string

    b _print_val
_square_4_chars:
    ldr r0, ptr_to_cursor_left
    mov r1, #0x36
    strb r1, [r0, #2]
    bl output_string

_print_val:
    ldr r0, ptr_to_square_val
    bl output_string

_exit_place_square:
	LDMFD sp!, {lr, r4-r11}
	mov pc, lr

clear_board:
    STMFD SP!,{lr, r4-r11}

    ldr r0, ptr_to_clear
    bl output_string

    bl output_boarder

	LDMFD sp!, {lr, r4-r11}
	mov pc, lr

;* loop unrolled
draw_board:
	STMFD SP!,{lr, r4-r11}
    mov r5, #0
    mov r6, #0

    ldr r4, ptr_to_subboard
    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    mov r5, #0
    add r6, r6, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    mov r5, #0
    add r6, r6, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    mov r5, #0
    add r6, r6, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    add r5, r5, #1

    ldrb r2, [r4]
    mov r0, r5
    mov r1, r6
    bl place_square
    add r4, r4, #1
    mov r5, #0
    add r6, r6, #1

	LDMFD sp!, {lr, r4-r11}
	mov pc, lr


shift_right_wrapper:
	STMFD SP!,{lr}

    ldr r0, ptr_to_subboard
    bl shift_right_op
    bl update_score

    bl draw_board

	LDMFD sp!, {lr}
	mov pc, lr

shift_left_wrapper:
	STMFD SP!,{lr}

    ldr r0, ptr_to_subboard
    bl shift_left_op
    bl update_score

    bl draw_board

	LDMFD sp!, {lr}
	mov pc, lr

shift_down_wrapper:
	STMFD SP!,{lr}

    ldr r0, ptr_to_subboard
    bl shift_down_op
    bl update_score

    bl draw_board

	LDMFD sp!, {lr}
	mov pc, lr

shift_up_wrapper:
	STMFD SP!,{lr}

    ldr r0, ptr_to_subboard
    bl shift_up_op
    bl update_score

    bl draw_board

	LDMFD sp!, {lr}
	mov pc, lr

;* updates the score in mem and on the LCD
;* input - r0 (added score)
update_score:
	STMFD SP!,{lr, r4-r11}

    ldr r4, ptr_to_score
    ldr r1, [r4]                ; load the value
    add r0, r0, r1              ; increment the score
    str r0, [r4]                ; store in memory

    ldr r1, ptr_to_score_string
    bl int2str                  ; convert to string

    mov r0, #7                  ; set LCD position
    mov r1, #1
    bl LCD_setCursor

    ldr r0, ptr_to_score_string
    bl LCD_print                ; output the score

	LDMFD sp!, {lr, r4-r11}
	mov pc, lr