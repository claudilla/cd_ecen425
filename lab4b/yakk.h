#ifndef YAKK_H
#define YAKK_H

/*Kernel Data Structures*/

typedef struct TCBlock *TCBptr; //pointer that points to the struct??


typedef struct TCBlock {				
	int	TCBId;			/* Task name or ID*/    
	void *stackptr;		/* pointer to current top of stack */
    int state;			/* current state */
    int priority;		/* current priority */
    TCBptr next;		/* forward ptr for linked list */
}  TCB;


void YKInitialize(void);
void YKIdleTask(void);
void YKNewTask(void (* task)(void), void *taskStack, unsigned char priority);
void YKRun(void);
//void YKDelayTask(unsigned count);
void YKEnterMutex(void);
void YKExitMutex(void);
//void YKEnterISR(void);
//void YKExitISR(void);
void YKScheduler(void);
void YKDispatcher(void);
//void YKTickHandler(void);
unsigned int YKCtxSwCount;
unsigned int YKIdleCount;

#endif
