YKEnterMutex:
    cli ;disable interrupts
    ret ;return from procedure or function


YKExitMutex:
    sti ;enble interrupts
    ret ;return from procedure or function


YKDispatcher_one:
    mov bx, word[YKReadyNextTask]  ; switch the top of the stack to next task to run
    mov sp,[bx] //move bx to sp

    mov bx, word[YKReadyNextTask]   ; move ready task to the runnin task
    mov word[YKcurrTask], bx   //restore context

	pop bp			; pop off reverse order, restore context
	pop es		
	pop ds
	pop di
	pop si

    pop DX
	pop CX
	pop BX
	pop AX

    iret


YKDispatcher:
//
//    pushf	 //save flags
//	push cs // save code segment offset for ip
	push word [bp+2] ;ip
		
	push AX			
	push BX		
	push CX
	push DX
	push si
	push di
	push ds
	push es
	push bp


	mov bx, word[YKcurrTask]
	mov [bx], sp

    mov bx, word[YKReadyNextTask] //put tcbpr next ready task to bp
    mov sp, [bx]  //put nextready task to current task
    mov bx, word[YKReadyNextTask]
    mov word[YKcurrTask], bx
    pop bp






	pop es
	pop ds
	pop di
	pop si

    pop DX
	pop CX
	pop BX
	pop AX
    iret










