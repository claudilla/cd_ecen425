#assembly code

YKNewTask:#???initialize registers here???
	

disable:
	cli				; clear IF flag/disable interrupts
	iret


enable:
	sti				; set IF flag/enable interrupts
	
