#include "queue.h"
#include "stack.h"
#include "time.h"

int main()
{
    Order *queue = NULL, *queue_bin = NULL;
    ExamPaper *stack = NULL, *stack_bin = NULL;
    
    queue = enqueue(queue,"Erdem",1111,"Dürüm,Ayran",time(NULL));
    queue = enqueue(queue,"Ali",1112,"Döner,Ayran",time(NULL));
    queue = enqueue(queue,"Mehmet",1113,"Kebap, Kola",time(NULL));
    queue = enqueue(queue,"Ahmet",1114,"Salata, Şalgam, Su",time(NULL));
    serializeFIFO(queue,"queue.bin");
    queue_bin = deserializeFIFO("queue.bin");
    Display_queue(queue_bin);

    
    queue = dequeue(queue);
    Display_queue(queue);

    stack = push(stack,"Erdem",1111,100);
    stack = push(stack,"Ali",1112,90);
    stack = push(stack,"Mehmet",1113,80);
    stack = push(stack,"Ahmet",1114,70);
    serializeLIFO(stack,"stack.bin");
    stack_bin = deserializeLIFO("stack.bin");
    Display_stack(stack_bin);

    Display_stack(stack);
    stack = pop(stack);
    Display_stack(stack);
}