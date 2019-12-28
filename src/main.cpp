/*==============================================================================
                        Magdalena Majkowska 
Bufor 9 elementowy FIFO. Dwóch konsumentów i dwóch producentów. Producent A
produkuję literę A, producent B produkuję literę B. Producent A może zapisywać
elementy do bufora jedynie gdy ich liczba elementów w buforze większa niż 5.
Odczyt (usunięcie) jest dozwolone, gdy liczba elementów w buforze jest większa 
niż 3. 
==============================================================================*/

#include "my_monitor.h"
#include "queue.h"
#include <iostream>

#define CONSUMER1_SLEEP 6
#define CONSUMER2_SLEEP 6
#define PRODUCERA_SLEEP 3
#define PRODUCERB_SLEEP 1

void wait(int how_much){
  usleep(1000000*how_much);
}

void * consumer1(void* ptr);
void * consumer2(void* ptr);
void * producerA(void* ptr);
void * producerB(void* ptr);

My_monitor monitor;

void * consumer1(void*ptr){
  //wait(CONSUMER1_SLEEP);
  while(1){
    monitor.consume(1);
    wait(CONSUMER1_SLEEP);
  }
}


void * consumer2(void * ptr){
  //wait(CONSUMER2_SLEEP);
  while(1){
    monitor.consume(2);
    wait(CONSUMER2_SLEEP);
  }
}


void * producerA(void * ptr){
  //wait(PRODUCERA_SLEEP);
  while(1){
    monitor.produceA();
    wait(PRODUCERA_SLEEP);
  }
}

void * producerB(void* ptr){
  //wait(PRODUCERB_SLEEP);
  while(1){
    monitor.produceB();
    wait(PRODUCERB_SLEEP);
  }
}


int main(void){
    //URUCHOMIENIE WĄTKÓW
    pthread_t konsument_1, konsument_2, producent_A, producent_B;

    pthread_create(&producent_A,NULL, producerA,NULL);
    pthread_create(&producent_B,NULL, producerB,NULL);
    pthread_create(&konsument_1,NULL, consumer1,NULL);
    pthread_create(&konsument_2,NULL, consumer2,NULL);

    pthread_join(producent_A, NULL);
    pthread_join(producent_B, NULL);
    pthread_join(konsument_1, NULL);
    pthread_join(konsument_2, NULL);
}
