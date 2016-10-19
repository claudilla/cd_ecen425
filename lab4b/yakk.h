#ifndef YAKK_H
#define YAKK_H

/*Kernel Data Structures*/



typedef struct TCBlock *TCBptr; //pointer that points to the struct??

typedef struct TCBlock {				
	int	TCBId;			/* Task name or ID*/    
	void *stackptr;		/* pointer to current top of stack */
	//void *ip;	// void (* task)(void)
    char state;			/* current state */
    int priority;		/* current priority */
    int delay;
    TCBptr next;		/* forward ptr for double linked list */
    TCBptr prev;       /* prev otr for double linked lsit*/
}  TCB;

extern int YKCtxSwCount;

typedef unsigned int UWORD;

void YKInitialize(void);
void YKIdleTask(void);
void YKNewTask(void (* task)(void), void *taskStack, unsigned char priority);
void YKRun(void);
void YKDispatcher_one(void);
void YKDispatcher();
void YKEnterMutex(void);
void YKExitMutex(void);
void YKScheduler(void);
void YKEnterISR(void);
void YKExitISR(void);




#endif
