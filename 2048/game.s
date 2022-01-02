    .data
test: .string "test", 0xA, 0xD, 0
    
    .text
    .global start

    .global output_boarder
    .global place_square
    .global draw_board 
    .global random_tile
    .global clear_board 
    .global shift_right_wrapper
    .global shift_left_wrapper
    .global shift_down_wrapper
    .global shift_up_wrapper

    .global output_string
    .global init

ptr_to_test: .word test

start:
    STMFD SP!,{r0-r12,lr}

    bl output_boarder
    bl random_tile
    bl random_tile

    bl draw_board

_again:
    wfi
    b _again

    LDMFD sp!, {r0-r12,lr}
    MOV pc, lr
