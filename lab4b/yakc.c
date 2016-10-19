#include "yakk.h"
#include "yaku.h"
#include "clib.h"

int IdleStk[idleSTACKSIZE];

TCBptr YKRdyTCBList;					/* a list of TCBs of all ready tasks in order of decreasing priority */
TCBptr YKemptyTCBList;					/* a list of available TCBs */
TCB    YKTCBArray[MAXTASKS+1];			/* array to allocate all needed TCBs (extra one is for the idle task) */
TCBptr YKcurrTask; //tasl executing
TCBptr YKReadyNextTask; //points to ready tasSK

unsigned int running;           /*  Flag to see if mt Kernel is running */
unsigned int depth;
int YKCtxSwCount;
unsigned int YKIdleCount;
unsigned int CurrPriority;     /* Priority task that is running */
unsigned int NextPriority;     /* Which one is the priority to excute next? */
unsigned int FirstDispatcherFlag;        /* This is flag is to know when my task is running for the first time*/


void YKInitialize(void)
{
    int i;
    printString("Init kernel.\n");
    /*init all global variables*/
    YKEnterMutex(); /* Don't get interrupted here*/
    YKCtxSwCount =0;
    YKIdleCount  =0;
    running   	 =0;
    depth 		 =0;
    CurrPriority =100;   /* Priority task that is running */
    NextPriority =0;/* Which one is the priority to excute next? */
    FirstDispatcherFlag=1;
    
    
    YKemptyTCBList = &(YKTCBArray[0]);          	/* Points list to first TCB */
    for (i = 0; i < MAXTASKS; i++)
        YKTCBArray[i].next = &(YKTCBArray[i+1]); 	/*This next is goingto receive that value*/
    YKTCBArray[MAXTASKS].next = NULL;
    YKNewTask(YKIdleTask, (void *)&IdleStk[idleSTACKSIZE],100 ); /*Create New Task*/
    
    
    YKcurrTask = YKRdyTCBList;
    YKReadyNextTask = YKRdyTCBList;
    
    
}

void YKIdleTask(void){
    
    while(1){
        YKEnterMutex(); /*Disable Interrupts*/
        YKIdleCount++;
        YKExitMutex(); /*Enable Interrupts*/
    }
    
}
void YKNewTask(void (* task)(void), void *taskStack, unsigned char priority){//and this one
    TCBptr newTask, tmp2;
    unsigned int *stack_ptr;
    stack_ptr =taskStack;
    
    // *--stack_ptr = (UWORD) 0x0001;   // empty space (ret address normally goes here)
    *--stack_ptr = (unsigned int) 0x0202;   // flags (maybe 0202?)
    *--stack_ptr = (unsigned int) 0x0000;   // CS
    *--stack_ptr = (unsigned int) task;     // IP (points to task code)
    *--stack_ptr = (unsigned int) 0x0000;   // AX (equivalent to push ax)
    *--stack_ptr = (unsigned int) 0x0000;   // BX
    *--stack_ptr = (unsigned int) 0x0000;   // CX
    *--stack_ptr = (unsigned int) 0x0000;   // DX
    //    *--stack_ptr = (UWORD) 0x0000;   // BP
    *--stack_ptr = (unsigned int) 0x0000;   // SI
    *--stack_ptr = (unsigned int) 0x0000;   // DI
    *--stack_ptr = (unsigned int) 0x0000;   // DS
    *--stack_ptr = (unsigned int) 0x0000;   // ES
    *--stack_ptr = (unsigned int) taskStack; // BP
    
    
    
    newTask = YKemptyTCBList; //putting first task to temp//
    YKemptyTCBList = newTask->next;
    newTask->stackptr = stack_ptr;
    newTask->state= 'r';
    newTask->priority = priority;
    newTask->delay =0;
    newTask->next = NULL;
    newTask->prev = NULL;
    if (YKRdyTCBList == NULL)	/* is this first insertion, checking for first time */
    {
        YKRdyTCBList = newTask;
        newTask->next = NULL;
        newTask->prev = NULL;
        
    }
    else			/* not first insertion */
    {
        tmp2 = YKRdyTCBList;	/* insert in sorted ready list */
        
        while (tmp2->priority < newTask->priority)
            tmp2 = tmp2->next;	/* assumes idle task is at end */
        
        
        if (tmp2->prev == NULL)	/* insert in list before tmp2 */
        {
            YKRdyTCBList = newTask;
            newTask->prev = NULL;
            newTask->prev = YKRdyTCBList;
            newTask->next->prev= newTask;
            
        }
        
        else{
            tmp2->prev->next = newTask;
            newTask->prev = tmp2->prev;
            newTask->next = tmp2;
            tmp2->prev = newTask;
        }
    }
    
    if(!running)
        YKRun();
    else
        YKScheduler();
}
void YKRun(void){
    YKExitMutex();
    /* Set global flag to indicate kernel started */
    running =1;
    YKScheduler();
    /* Call scheduler for first time */
    //one user defined task must be created before this is called
    
}


void YKEnterISR(void){
    
    depth++;
}

void YKExitISR(void){
    
    depth--;
    if(depth ==0)
        YKScheduler();
}

void YKScheduler(void){
    
    TCBptr tmp;
    if (running == 1){
        YKEnterMutex();
        tmp=YKRdyTCBList;
        
        while( tmp->next != NULL){ //while thre is another task in tmp
            tmp->state = 'r'; //if temp is ready
            break;
            tmp = tmp->next; //tmp points to highest priority of the ready task
        }
        
        
        NextPriority= tmp->priority;
        YKReadyNextTask= tmp;
        
        if( CurrPriority != NextPriority){
            YKCtxSwCount++;
            CurrPriority = NextPriority;
            
            if(FirstDispatcherFlag == 1){
                FirstDispatcherFlag=0;
                YKDispatcher_one(); //first dispatcher
            }else{
                asm("pushf");   //pushing flags/
                asm("push cs"); //
                YKDispatcher();
            }
        }
    }
    YKExitMutex();
}

