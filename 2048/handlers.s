    .data
time_string:    .string "00:00:00", 0
time_int:       .int 0

game_active     .char 0     ; 1 when active, 0 by default
    .text
    .global Timer_Handler
    .global Switch_Handler
    .global Keypad_Handler
    .global UART0_Handler

    .global shift_right_wrapper
    .global shift_left_wrapper
    .global shift_down_wrapper
    .global shift_up_wrapper

    .global start_game

    ;* lib
    .export time_to_string

    ;* LCD
    ;* .include LCD.h
    .export LCD_print
    .export LCD_setCursor

    ;* library
    .global read_character
    .global read_from_push_btn
    .global output_character

    ;* keypad
    .export keypad_clear_interrupt
    .export keypad_read
    .export keypad_wait

ptr_to_time_string: .word time_string
ptr_to_time_int:    .word time_int

ptr_to_game_active: .word game_active

W:  .equ 0x77
A:  .equ 0x61
S:  .equ 0x73
D:  .equ 0x64
ENTER: .equ 0xD

;************************Handlers************************
;* clear timer interrupt and does "stuff"
;* input  -
;* output -
Timer_Handler:
    STMFD SP!,{r0-r12,lr}

    ; Clear the interrupt
    mov r0, #0x0000
    movt r0, #0x4003
    ldrb r1, [r0,#0x024]
    orr r2,r1 ,#1
    strb r2, [r0,#0x024]

    ldr r0, ptr_to_game_active
    ldrb r0, [r0]
    cmp r0, #0
    beq _exit_timer_handler

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

_exit_timer_handler
    LDMFD sp!, {r0-r12,lr}
    BX lr

;* clear switch interrupt and does "stuff"
;* input  -
;* output -
Switch_Handler:
    STMFD SP!,{r0-r12,lr}

    mov r1, #0x5000
    movt r1, #0x4002
    ldrb r2, [r1,#0x41C]
    orr r3, r2, #0x10
    strb r3, [r1,#0x41C]

    bl read_from_push_btn

    LDMFD sp!, {r0-r12,lr}
    BX lr

;* clear switch interrupt and does operation
;* input  -
;* output -
Keypad_Handler:
    STMFD SP!,{r0-r12,lr}
    bl keypad_clear_interrupt

    bl keypad_wait
    cmp r0, #0
    beq _exit_Keypad_Handler

    bl keypad_read
    mov r4, r0

    ldr r0, ptr_to_game_active
    ldrb r0, [r0]
    cmp r0, #0
    beq _exit_Keypad_Handler

    mov r0, r4
    bl board_move
_exit_Keypad_Handler:
    LDMFD sp!, {r0-r12,lr}
    BX lr

;* clear UART interrupt and does "stuff"
;* input  -
;* output -
UART0_Handler:
	STMFD SP!,{r0-r12,lr}

    mov r0, #0xC000
    movt r0, #0x4000
    ldrb r1, [r0,#0x044]
    mov r2, #1
    bfi r1, r2, #4, #1  ; place 1 to clear interrupt
    strb r1, [r0,#0x044]
    
    bl read_character

    ldr r4, ptr_to_game_active
    ldrb r4, [r4]
    cmp r4, #0
    bne _board_mover

    cmp r0, #ENTER
    bne _exit_UART_Handler

    mov r0, #1
    ldr r1, ptr_to_game_active
    strb r0, [r1]
    bl start_game

    b _exit_UART_Handler
_board_mover:
    bl board_move
_exit_UART_Handler:
    LDMFD sp!, {r0-r12,lr}
    BX lr

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


.end
