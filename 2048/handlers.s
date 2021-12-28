    .data

    .text
    .global Timer_Handler
    .global Switch_Handler
    .global UART0_Handler

;************************Handlers************************
;* clear timer interupt and does "stuff"
;* input  -
;* output -
Timer_Handler:
    STMFD SP!,{r0-r12,lr}

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
