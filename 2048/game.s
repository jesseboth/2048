    .data
game_active     .char 0     ; 1 when active, 0 by default
time_string:    .string "00:00:00", 0
time_int:       .int 0

    .text
    .global start
    .global start_game
    .global update_timer
    .global game_input
    .global board_move
    .global game_over

    ;* board
    .global output_boarder
    .global place_square
    .global draw_board 
    .global random_tile
    .global clear_board 
    .global make_title
    .global make_end
    .global get_score
    .global zero_score
    .global clear_subboard

    ;* shift
    .global shift_right_wrapper
    .global shift_left_wrapper
    .global shift_down_wrapper
    .global shift_up_wrapper

    ;* library
    .global output_string
    .global init

    ;* lib
    .export time_to_string

    ;* LCD
    .export LCD_print
    .export LCD_setCursor

ptr_to_game_active: .word game_active
ptr_to_time_string: .word time_string
ptr_to_time_int:    .word time_int

W:  .equ 0x77
A:  .equ 0x61
S:  .equ 0x73
D:  .equ 0x64
ENTER: .equ 0xD

start:
    STMFD SP!,{r0-r12,lr}

    bl make_title

_again:
    wfi
    b _again

    LDMFD sp!, {r0-r12,lr}
    MOV pc, lr

;* starts the game
start_game:
    STMFD SP!,{r0-r12,lr}

    ldr r0, ptr_to_time_int
    eor r1, r1, r1
    str r1, [r0]

    bl zero_score
    bl clear_subboard

    bl output_boarder
    bl random_tile
    bl random_tile

    bl draw_board

    LDMFD sp!, {r0-r12,lr}
    MOV pc, lr

;* Update the timer
update_timer:
    STMFD SP!,{r4-r12,lr} 

    ldr r0, ptr_to_game_active
    ldrb r0, [r0]
    cmp r0, #0
    beq _exit_update_timer

    ldr r4, ptr_to_time_int
    ldr r0, [r4]
    add r0, r0, #1
    str r0, [r4]

    ldr r1, ptr_to_time_string
    bl time_to_string

    mov r0, #6
    mov r1, #0
    bl LCD_setCursor

    ldr r0, ptr_to_time_string
    bl LCD_print

_exit_update_timer
    LDMFD sp!, {r4-r12,lr}       
    MOV pc, lr

;* Determines if game manipulation should occur
;* input - r0 (char)
game_input:
    STMFD SP!,{r4-r12,lr} 

    ldr r4, ptr_to_game_active
    ldrb r4, [r4]
    cmp r4, #0
    bne _board_mover

    cmp r0, #ENTER
    bne _exit_game_input

    mov r0, #1
    ldr r1, ptr_to_game_active
    strb r0, [r1]
    bl start_game

    b _exit_game_input
_board_mover:
    bl board_move

_exit_game_input
    LDMFD sp!, {r4-r12,lr}       
    MOV pc, lr

;* moves the board from interrupt
;* input - r0 (WASD)
board_move:
    STMFD SP!,{r4-r12,lr} 
    
    cmp r0, #W
    beq _up_pressed

    cmp r0, #A
    beq _left_pressed

    cmp r0, #S
    beq _down_pressed

    cmp r0, #D
    beq _right_pressed

    b _exit_board_move

_up_pressed:
    bl shift_up_wrapper
    b _exit_board_move
_left_pressed:
    bl shift_left_wrapper
    b _exit_board_move
_down_pressed:
    bl shift_down_wrapper
    b _exit_board_move
_right_pressed:
    bl shift_right_wrapper

_exit_board_move:
    LDMFD sp!, {r4-r12,lr}       
    MOV pc, lr

game_over:
	STMFD SP!,{lr, r4-r11}

    bl get_score

    ldr r1, ptr_to_time_string
    bl make_end

    ldr r0, ptr_to_game_active
    eor r1, r1, r1
    str r1, [r0]


	LDMFD sp!, {lr, r4-r11}
	mov pc, lr