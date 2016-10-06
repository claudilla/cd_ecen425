YKEnterMutex:
    cli ;disable interrupts
    ret ;return from procedure or function


YKExitMutex:
    sti ;enble interrupts
    ret ;return from procedure or function




YKDispatcher:
    push bx
    mov bx, word[nextPriority]
    cmp bx, word[cur]
    pop bx
    jne YKSaveContxt


    jump if it is not equal


    //context is the register that has some values .. ax, bx.//
YKSaveContext: //second time running u save context


        inc word
        push ax
        push bx
        push cx
        push dx

            pop




            mov si, word[runnintask]

            jmp YKDispatcher
            