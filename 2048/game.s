    .data
    
    .text
    .global start
    .global start_game

    .global output_boarder
    .global place_square
    .global draw_board 
    .global random_tile
    .global clear_board 
    .global make_title

    .global output_string
    .global init

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

    bl output_boarder
    bl random_tile
    bl random_tile

    bl draw_board

    LDMFD sp!, {r0-r12,lr}
    MOV pc, lr