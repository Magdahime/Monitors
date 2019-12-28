#include "queue.h"
#include <string.h>
char peek(struct FIFOqueue queue){
    return queue.queue[queue.tail];
}
int size(struct FIFOqueue queue){
    return queue.item_count;
}
bool isEmpty(struct FIFOqueue queue) {
    return (queue.item_count==0);
}

bool isFull(struct FIFOqueue queue) {
    return (queue.item_count==MAX);
}
void insert(struct FIFOqueue* queue, char* data) {
    if(!isFull(*queue)&& strlen(data)<2){

        if(queue->tail==MAX-1){
            queue->queue[queue->head-1] = *data;
            queue->item_count++;
            queue->head=queue->head-1;
        }else{
        for(int i=MAX-1; i>0; i--){
            queue->queue[i]=queue->queue[i-1];      //SHIFT THE QUEUE
        }
        queue->queue[queue->head] = *data;
        queue->item_count++;
        queue->tail++;
    }
            //printf("DHEAD: %d\t",queue->head);
            //printf("DTAIL: %d\n",queue->tail);
}
}
int removeData(struct FIFOqueue* queue) {
    if(!isEmpty(*queue)){
    int data = queue->queue[queue->tail];
    queue->queue[queue->tail]=0;
    for(int i=MAX-1; i>0; i--){
        queue->queue[i]=queue->queue[i-1];      //SHIFT THE QUEUE
    }
    queue->queue[queue->head]=0;
    queue->head++;
    if(queue->head == queue->tail && queue->item_count==0){
        queue->head =0;
        queue->tail=-1;
    }
    queue->item_count--;
        //printf("RHEAD: %d\t",queue->head);
        //printf("RTAIL: %d\n",queue->tail);
    return data;
}
}

void read_queue(struct FIFOqueue queue){
    printf("\t[ ");
    for(int i=0; i<MAX; i++){
        if(queue.queue[i]<65 ||queue.queue[i]> 90) printf("_ ");
        else printf("%c ", queue.queue[i]);
    }
        printf("]\n");
}