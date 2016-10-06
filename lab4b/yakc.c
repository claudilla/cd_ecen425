#define NULL 0
#define MAXTASKS 3					/* count of user tasks */
#define idleSTACKSIZE 256 
int IdleStk[idleSTACKSIZE];

TCBptr YKRdyList;					/* a list of TCBs of all ready tasks
				   						in order of decreasing priority */ 

TCBptr YKAvailTCBList;		/* a list of available TCBs */
TCB    YKTCBArray[MAXTASKS+1];	/* array to allocate all needed TCBs
				   (extra one is for the idle task) */


//claudiaaaaaa

void YKInitialize(void)
{
	int i;
	YKAvailTCBList = &(YKTCBArray[0]);
    for (i = 0; i < MAXTASKS; i++)
	YKTCBArray[i].next = &(YKTCBArray[i+1]);
    YKTCBArray[MAXTASKS].next = NULL;	
	
	YKINewTask(YKIdleTask, (void *)&IdleSTK[idleSTACKSIZE],100 ); /*Create New Task*/
	
}

void YKIdleTask(void){//and this one

	while(1){
		YKIdlecount++;
	}

}
void YKNewTask(void (* task)(void), void *taskStack, unsigned char priority){//and this one

    	TCBptr tmp, tmp2;
    	tmp = YKAvailTCBList;
    	YKAvailTCBList = tmp->next;
		
		if (YKRdyList == NULL)	/* is this first insertion */
		{
			YKRdyList = tmp;
			tmp->next = NULL;
			tmp->prev = NULL;
		}
		else			/* not first insertion */
		{
			tmp2 = YKRdyList;	/* insert in sorted ready list */
		while (tmp2->priority < tmp->priority)
			tmp2 = tmp2->next;	/* assumes idle task is at end */
		if (tmp2->prev == NULL)	/* insert in list before tmp2 */
			YKRdyList = tmp;
		else
			tmp2->prev->next = tmp;
			tmp->prev = tmp2->prev;
			tmp->next = tmp2;
			tmp2->prev = tmp;
		}



/* Each time YKNewTask is called, you will want to allocate and initialize a new TCB. For purposes of efficiency you should avoid dynamic allocation (e.g., malloc); instead, think about declaring an array of TCB structs in your code and doing your own allocation from the array.*/
	
}
void YKRun(void){
	/* Set global flag to indicate kernel started */
    
    /* Call scheduler for first time */
	//one user defined task must be created before this is called

}

void YKEnterMutex(void){
	/*This function disables interrupts. It may be called from application or system code.*/
	//call assembly code
	disable();
}
void YKExitMutex(void){
	/*This function enables interrupts. It may be called from application or system code.*/
	//call assembly code
	enable();
}

void YKScheduler(void){


}
void YKDispatcher(void){

}
void YKTickHandler(void){


}
unsigned int YKCtxSwCount;
unsigned int YKIdleCount;



