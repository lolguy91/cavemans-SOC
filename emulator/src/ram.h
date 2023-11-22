#include "bus.h"
#include <pthread.h> 
__UINT8_TYPE__* ram_data;
__uint16_t ram_size;
__uint16_t ram_start;
__UINT8_TYPE__ ram_subfunc(__UINT16_TYPE__ addr,__UINT8_TYPE__ val,int rw){
    if(addr > ram_size || (short)addr - (short)ram_start < 0){
        printf("ram balls %i\n",addr);
        return 0;
    }
    if(!rw){//read
        return ram_data[addr - ram_start];
    }else{//write
        ram_data[addr - ram_start] = val;
        return 0;
    }
}

void make_ram(bus bus,__uint16_t size,__uint16_t start){
    if(start + size > 65535){
        return;
    }
    ram_data = malloc(size);
    ram_start = start;
    ram_size = size;
    bus_subscribe(bus,ram_subfunc);
}