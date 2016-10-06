resetisr:
	; move all registers onto the stack, except sp, ss, cs, ip, and the flags
	;push AX			; push AX onto the stack
	;push BX		
	;push CX
	;push DX
	;push si
	;push di
	;push bp
	;push es
	;push ds
	sti				; set IF flag/enable interrupts
	call reseth		; call the c function
	cli				; clear IF flag/disable interrupts
	mov	al, 0x20	; Load nonspecific EOI value (0x20) into register al STEP 5******
	out	0x20, al	; Write EOI to PIC (port 0x20)

	;pop all of the registers off and return
	;pop AX			; pop AX onto the stack
	;pop BX		
	;pop CX
	;pop DX
	;pop si
	;pop di
	;pop bp
	;pop es
	;pop ds
	iret

tickisr:
	; move all registers onto the stack, except sp, ss, cs, ip, and the flags
	push AX			; push AX onto the stack
	push BX		
	push CX
	push DX
	push si
	push di
	push bp
	push es
	push ds
	sti				; set IF flag/enable interrupts
	call tickh		; call the c function
	cli				; clear IF flag/disable interrupts
	mov	al, 0x20	; Load nonspecific EOI value (0x20) into register al STEP 5******
	out	0x20, al	; Write EOI to PIC (port 0x20)

	; pop all of the registers off and return
	pop ds			; pop off reverse order
	pop es		
	pop bp
	pop di
	pop si
	pop DX
	pop CX
	pop BX
	pop AX
	iret

keyboardisr:
	; move all registers onto the stack, except sp, ss, cs, ip, and the flags
	push AX			;push AX onto the stack
	push BX		
	push CX
	push DX
	push si
	push di
	push bp
	push es
	push ds
	sti				; set IF flag/enable interrupts
	call keyboardh	; call the c function
	cli				; clear IF flag/disable interrupts
	mov	al, 0x20	; Load nonspecific EOI value (0x20) into register al STEP 5******
	out	0x20, al	; Write EOI to PIC (port 0x20)

	; pop all of the registers off and return
	pop ds			; pop off reverse order
	pop es		
	pop bp
	pop di
	pop si
	pop DX
	pop CX
	pop BX
	pop AX
	iret

