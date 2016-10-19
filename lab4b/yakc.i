# 1 "yakc.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "yakc.c"
# 1 "yakk.h" 1







typedef struct TCBlock *TCBptr;

typedef struct TCBlock {
 int TCBId;
 void *stackptr;
 void *ip;
    char state;
    int priority;
    TCBptr next;
    TCBptr prev;
} TCB;


void YKInitialize(void);
void YKIdleTask(void);
void YKNewTask(void (* task)(void), void *taskStack, unsigned char priority);
void YKRun(void);
void YKEnterMutex(void);
void YKExitMutex(void);
void YKScheduler(void);
void YKDispatcher(void);

void ISRDispatcher(void);
void ISREnterMutex(void);
void ISRExitMutex(void);



extern unsigned int YKCtxSwCount;
extern unsigned int YKIdleCount;
# 2 "yakc.c" 2
# 1 "yaku.h" 1
# 3 "yakc.c" 2
# 1 "clib.h" 1



void print(char *string, int length);
void printNewLine(void);
void printChar(char c);
void printString(char *string);


void printInt(int val);
void printLong(long val);
void printUInt(unsigned val);
void printULong(unsigned long val);


void printByte(char val);
void printWord(int val);
void printDWord(long val);


void exit(unsigned char code);


void signalEOI(void);
# 4 "yakc.c" 2




int IdleStk[256];

TCBptr YKRdyTCBList;
TCBptr YKemptyTCBList;
TCB YKTCBArray[3 +1];
TCBptr YKcurrTask;

unsigned int running;
unsigned int depth;
unsigned int YKCtxSwCount;
unsigned int YKIdleCount;
unsigned int CurrPriority;
unsigned int NextPriority;


void YKInitialize(void)
{
    int i;
    printString("Init kernel.\n");

    YKCtxSwCount =0;
    YKIdleCount =0;
    running =0;
 depth = 0;

    YKemptyTCBList = &(YKTCBArray[0]);
    for (i = 0; i < 3; i++)
        YKTCBArray[i].next = &(YKTCBArray[i+1]);
    YKTCBArray[3].next = 0;
    YKNewTask(YKIdleTask, (void *)&IdleStk[256],100 );

}

void YKIdleTask(void){

    while(1){
        YKEnterMutex();
        YKIdleCount++;
        YKExitMutex();
    }

}
void YKNewTask(void (* task)(void), void *taskStack, unsigned char priority){

 TCBptr newTask, tmp2;

    newTask = YKemptyTCBList;
    YKemptyTCBList = newTask->next;

    if (YKRdyTCBList == 0)
    {
        YKRdyTCBList = newTask;
        newTask->next = 0;
        newTask->prev = 0;

    }
    else
    {
        tmp2 = YKRdyTCBList;
        while (tmp2->priority < newTask->priority)
            tmp2 = tmp2->next;


  if (tmp2->prev == 0)
   {
   YKRdyTCBList = newTask;
         newTask->prev = 0;
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
}
# 96 "yakc.c"
}
void YKRun(void){

    running =1;
    YKScheduler();



}

void YKEnterMutex(void){


 ISREnterMutex();

}
void YKExitMutex(void){


   ISRExitMutex();
}

void YKEnterISR(void){


}

void YKScheduler(void){





 if (running == 1);
  YKEnterMutex();
  tmp=YKRdyTCBList;

    while( tmp->next != 0){
        tmp->state = 'r';
        break;
        tmp = tmp->next;
}

 NextPriority= temp->priority;
 nextReadyTask= tmp;

    if( CurrPriority != NextPriority){
  YKCtxSwCount++;
  CurrPriority = NextPriority;

   if(YKIdleCount == 1){
     YKIdleCount=0;
    YKDispatcher_one();
   }else{
   asm("pushf");
   asm("push cs");
   YKDispatcher():
  }
 }
}

}

void YKDispatcher_one(void){




}

void YKDispatcher(void){




 printString("Entering YKDispatcher\n");
 taskpriority = YKcurrTask->priority;
 nexttaskpriority = YKcurrTask->next->priority;
 ISRDispatcher();
}
