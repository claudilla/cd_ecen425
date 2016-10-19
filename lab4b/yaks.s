YKEnterMutex:
    push bp
    mov bp, sp

    cli ;disable interrupts

    mov sp, bp
    pop bp


    ret ;return from procedure or function


YKExitMutex:

    push bp
    mov bp, sp

    sti ;enble interrupts

    mov sp, bp
    pop bp
    ret ;return from procedure or function




YKDispatcher:


		
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

    mov bx, word[YKReadyNextTask]
    mov sp, [bx]
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

YKDispatcher_one:
    mov bx, word[YKReadyNextTask]  ; switch the top of the stack to next task to run
    mov sp, [bx]

    mov bx, word[YKReadyNextTask]   ; move ready task to the runnin task
    mov word[YKcurrTask], bx   

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









