    .data

    .text
    .global Timer_Handler
    .global Switch_Handler
    .global Keypad_Handler
    .global UART0_Handler

    ;* game
    .global update_timer
    .global game_input

    ;* library
    .global read_character
    .global read_from_push_btn

    ;* keypad
    .export keypad_clear_interrupt
    .export keypad_read
    .export keypad_wait

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
    bl game_input

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
    bl game_input
    
_exit_UART_Handler:
    LDMFD sp!, {r0-r12,lr}
    BX lr


.end
