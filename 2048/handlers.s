    .data
time_string:    .string "00:00:00", 0
time_int:       .int 0

game_active     .char 1     ; 1 when active, 0 by default
    .text
    .global Timer_Handler
    .global Switch_Handler
    .global UART0_Handler

    ;* lib
    .export time_to_string

    ;* LCD
    ;* .include LCD.h
    .export LCD_print
    .export LCD_setCursor

ptr_to_time_string: .word time_string
ptr_to_time_int:    .word time_int

ptr_to_game_active: .word game_active

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


    LDMFD sp!, {r0-r12,lr}
    BX lr

.end
