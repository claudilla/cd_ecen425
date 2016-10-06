#define NULL 0
#define MAXTASKS 3					/* count of user tasks */
#define idleSTACKSIZE 256
int IdleStk[idleSTACKSIZE];

TCBptr YKRdyList;					/* a list of TCBs of all ready tasks
                                     in order of decreasing priority */

TCBptr YKAvailTCBList;		/* a list of available TCBs */
TCB    YKTCBArray[MAXTASKS+1];	/* array to allocate all needed TCBs
                                 (extra one is for the idle task) */

TCBptr currTask;

int running;



void YKInitialize(void)
{
    int i;
    printString(" Init kernel");
    //init all global variables
    
    YKCtxSwCount =0;
    YKIdleCount  =0;
    running     =0;
    
    YKAvailTCBList = &(YKTCBArray[0]);          /* Points list to first TCB */
    for (i = 0; i < MAXTASKS; i++)
        YKTCBArray[i].next = &(YKTCBArray[i+1]); //This next is goingto receive that value/
    YKTCBArray[MAXTASKS].next = NULL;
    YKINewTask(YKIdleTask, (void *)&IdleSTK[idleSTACKSIZE],100 ); /*Create New Task*/
    
}

void YKIdleTask(void){
    
    while(1){
        YKEnterMutex(); /*Disable Interrupts*/
        YKIdlecount++;
        YKExitMutex(); /*Enable Interrupts*/
    }
    
}
void YKNewTask(void (* task)(void), void *taskStack, unsigned char priority){//and this one
    
    TCBptr tmp, tmp2;
    
    tmp = YKAvailTCBList; //putting first task to temp//
    YKAvailTCBList = tmp->next;
    
    if (YKRdyList == NULL)	/* is this first insertion, checking for first time */
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
    //set priority
    //stack pointer tmp->priotury = [rtipt
    
    
    //why do we want to point to bottom?
    // tmp->state /// whch state?
    
    //if it is not running.. execure yrun
    // but it is running execute scheduler
    
    
    
    
    
    
    /* Each time YKNewTask is called, you will want to allocate and initialize a new TCB. For purposes of efficiency you should avoid dynamic allocation (e.g., malloc); instead, think about declaring an array of TCB structs in your code and doing your own allocation from the array.*/
    
}
void YKRun(void){
    /* Set global flag to indicate kernel started */
    running =1;
    YKScheduler();
    /* Call scheduler for first time */
    //one user defined task must be created before this is called
    
}

void YKEnterMutex(void){
    /*This function disables interrupts. It may be called from application or system code.*/
    //call assembly code
     
}
void YKExitMutex(void){
    /*This function enables interrupts. It may be called from application or system code.*/
    //call assembly code
  
}

void YKScheduler(void){
    /*  Create pointer
     Disable interrupts
     Set Current task equal to ready Task
     While there is something in the struct (tmp->next)
     It is going to look if the state is running ex. tmp->state = "running"
     If it is running we want to break
     We want to go to next temp
     If temp is not the current task
     currTask == temp
     Increment count
     Call dispatcher
     Enable Interrupts
     
     */
    TCBptr tmp;
    YKEnterMutex();
    curr_task = YKRdyList;
    
    while( tmp->next != NULL){
        tmp->state = "r";
        break;
        temp = temp->next;
        
        if(temp != currTask){
            YKDispatcher();
        }
        YKExitMutex();
    }
    
    
    
}
void YKDispatcher(void){
    
}
void YKTickHandler(void){
    
    
}
unsigned int YKCtxSwCount;
unsigned int YKIdleCount;



