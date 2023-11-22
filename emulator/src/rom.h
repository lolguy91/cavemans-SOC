#include "bus.h"
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
__UINT8_TYPE__* rom_data;
__uint16_t rom_size;
__uint16_t rom_start;
__UINT8_TYPE__ rom_subfunc(__UINT16_TYPE__ addr,__UINT8_TYPE__ val,int rw){
    if(addr > rom_size || (short)addr - (short)rom_start < 0){
        printf("rom balls %i\n",addr);
        return 0;
    }
    return rom_data[addr - rom_start];
}

void make_rom(bus bus,__uint16_t size,__uint16_t start, char* filepath){
    if(start + size > 65535){
        return;
    }
    FILE* f = fopen(filepath,"rb");
    rom_data = (__UINT8_TYPE__*)malloc(size);
    fread(rom_data,size,1,f);
    fclose(f);
    rom_start = start;
    rom_size = size;
    bus_subscribe(bus,rom_subfunc);
}