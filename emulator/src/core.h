#include "bus.h"
#include <pthread.h> 
typedef struct {
    bus mainbus;
    bus extbus;
    int halted;
    __UINT16_TYPE__ ip;
    __UINT16_TYPE__ pc;
    __UINT8_TYPE__ rega;
    __UINT8_TYPE__ regb;
} core;
void *core_thread(void *vargp) 
{ 
    core* c = (core*)vargp;
    
    c->ip = bus_read(c->extbus,0);
    c->ip |= bus_read(c->extbus,1) << 8;
    while(1){
        if(c->halted){
            continue;
        }
        //printf("\e[1;1H\e[2J");
        //printf("A register : 0x%x\n",c->rega);
        //printf("B register : 0x%x\n",c->regb);

        __UINT8_TYPE__ tmp = bus_read(c->extbus,c->ip);
        switch ((tmp & 0xf0))
        {   
            case 0x00://add
                c->ip++;
                __UINT8_TYPE__ a = (tmp & 3);
                __UINT8_TYPE__ b = (tmp & 12);
                if(a == 0){
                    a = c->rega;
                }else if(a == 1){
                    a = c->regb;
                }
                if(b == 0){// its a 1, just lazy to bitshift
                    b = c->rega;
                    c->rega = a + b;
                    printf("A register : 0x%x\n",c->rega);
                }else if(b == 4){// its a 2, just lazy to bitshift
                    b = c->regb;
                    c->regb = a + b;
                    printf("B register : 0x%x\n",c->regb);
                }
                break;
            case 0x10://ina
                c->rega = bus_read(c->extbus,c->ip + 1);
                c->ip+= 2;
            case 0x20://inb
                c->regb = bus_read(c->extbus,c->ip + 1);
                c->ip+= 2;
            case 0xF0://hlt
                c->halted = 1;
            default:
                c->ip++;
                c->pc++;
                break;
        }

    }
    free(vargp);
    return NULL; 
}

void make_core(bus bus){
    core* c = malloc(sizeof(core));
    c->extbus = bus;
    c->mainbus = create_bus();
    pthread_t tid; 
    pthread_create(&tid, NULL, core_thread, (void *)c); 
}