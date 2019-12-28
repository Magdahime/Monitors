#include <iostream>
#include "queue.h"
#include "monitor.h"
class My_monitor : public Monitor{
    private:
    Condition full, ready_to_eat, wakeupA;
    FIFOqueue queue;
    public:
    My_monitor();
    void consume(int num);
    void produceA();
    void produceB();
};

My_monitor::My_monitor(){

    queue.tail =-1;
    queue.head=0;
    queue.item_count=0;

}
void My_monitor::consume(int num){
    enter();
    std::cout<<"Konsument nr"<<num<<" próbuje zdjąć coś z kolejki."<<std::endl;
    if(size(queue)<=3){
        wait(ready_to_eat);
    }
    std::cout<<"Konsument nr"<<num<<" zdejmuje z kolejki:"<<peek(queue)<<std::endl;
    char ret = removeData(&queue);
    read_queue(queue);
    std::cout<<"Konsument nr"<<num<<" konsumuje: "<<ret<<std::endl;
    if(size(queue)>5){
        signal(wakeupA);                //Sprawdzamy czy jest odpowiednia ilość dla producenta A
    }
    signal(full);
    leave();
}

void My_monitor::produceA(){
    enter();
    std::cout<<"Producent A próbuje dodać coś do kolejki."<<std::endl;
    if(size(queue)==MAX){
        signal(ready_to_eat);           //Staramy się obudzić jakiegoś konsumenta
        wait(full);                     //Sami kładziemy się spać
    }
    if(size(queue)<=5){
        wait(wakeupA);
    }
    std::cout<<"Producent A dodaje do kolejki."<<std::endl;
    insert(&queue,"A");
    read_queue(queue);
    signal(ready_to_eat);               //Dodaliśmy coś więc budzimy konsumentów
    leave();
}

void My_monitor::produceB(){
    enter();
    std::cout<<"Producent B próbuje dodać coś do kolejki."<<std::endl;
    if(size(queue)==MAX){
        signal(ready_to_eat);           //Staramy się obudzić jakiegoś konsumenta
        wait(full);
    }
    std::cout<<"Producent B dodaje do kolejki."<<std::endl;
    insert(&queue,"B");
    read_queue(queue);
    if(size(queue)>3){
        signal(ready_to_eat);           //Więcej niż 3 elementy w kolejce więc dajemy znać konsumentom
    }
    if(size(queue)>5){
        signal(wakeupA);              //Jest już więcej niż 5 więc możemy obudzić producenta A
    }
    leave();
}