    .data
test: .string "test", 0xA, 0xD, 0
    
    .text
    .global start

    .global output_boarder
    .global place_square
    .global draw_board 
    .global clear_board 
    .global shift_right_wrapper

    .global output_string
    .global init

ptr_to_test: .word test

start:
    STMFD SP!,{r0-r12,lr}

    ;ldr r0, ptr_to_test
    ;bl output_string

    bl output_boarder

    ;* mov r0, #3
    ;* mov r1, #3
    ;* mov r2, #4
    ;* bl place_square

    bl draw_board
    bl clear_board

    bl shift_right_wrapper
    bl draw_board

    orr r0, r0, r0

    LDMFD sp!, {r0-r12,lr}
    MOV pc, lr
