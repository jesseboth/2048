    .data
time_string:    .string "00:00:00", 0
time_int:       .int 0
prev_mov:       .char 0

game_active     .char 1     ; 1 when active, 0 by default
    .text
    .global Timer_Handler
    .global Switch_Handler
    .global UART0_Handler

    .global shift_right_wrapper
    .global shift_left_wrapper
    .global shift_down_wrapper
    .global shift_up_wrapper

    ;* lib
    .export time_to_string

    ;* LCD
    ;* .include LCD.h
    .export LCD_print
    .export LCD_setCursor

    ;* library
    .global read_character

ptr_to_time_string: .word time_string
ptr_to_time_int:    .word time_int
ptr_to_prev_mov:    .word prev_mov

ptr_to_game_active: .word game_active

W:  .equ 0x77
A:  .equ 0x61
S:  .equ 0x73
D:  .equ 0x64

;************************Handlers************************
;* clear timer interupt and does "stuff"
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

;* clear switch interupt and does "stuff"
;* input  -
;* output -
Switch_Handler:
    STMFD SP!,{r0-r12,lr}


    LDMFD sp!, {r0-r12,lr}
    BX lr

;* clear UART interupt and does "stuff"
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

    ldr r0, ptr_to_game_active
    ldrb r0, [r0]
    cmp r0, #0
    beq _exit_UART_Handler

    bl read_character
    mov r4, r0
    ldr r5, ptr_to_prev_mov
    ldrb r1, [r5]
    
    cmp r4, #W
    beq _up_pressed

    cmp r4, #A
    beq _left_pressed

    cmp r4, #S
    beq _down_pressed

    cmp r4, #D
    beq _right_pressed

    b _exit_UART_Handler

_up_pressed:
    bl shift_up_wrapper
    b _store_mov
_left_pressed:
    bl shift_left_wrapper
    b _store_mov
_down_pressed:
    bl shift_down_wrapper
    b _store_mov
_right_pressed:
    bl shift_right_wrapper
_store_mov:
    strb r4, [r5]
_exit_UART_Handler:
    LDMFD sp!, {r0-r12,lr}
    BX lr

.end
