#ifndef YAKK_H
#define YAKK_H

/*Kernel Data Structures*/

//gedit

typedef struct TCBlock *TCBptr; //pointer that points to the struct??

typedef struct TCBlock {				
	int	TCBId;			/* Task name or ID*/    
	void *stackptr;		/* pointer to current top of stack */
    char state;			/* current state */
    int priority;		/* current priority */
    TCBptr next;		/* forward ptr for double linked list */
    TCBptr prev;       /* prev otr for double linked lsit*/
}  TCB;


void YKInitialize(void);
void YKIdleTask(void);
void YKNewTask(void (* task)(void), void *taskStack, unsigned char priority);
void YKRun(void);
void YKEnterMutex(void);
void YKExitMutex(void);
void YKScheduler(void);
void YKDispatcher(void);

//global variable//

unsigned int YKCtxSwCount;
unsigned int YKIdleCount;


#endif