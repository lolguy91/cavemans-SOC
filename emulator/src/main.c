#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 
#include "core.h"
#include "ram.h"
#include "rom.h"

int main(int argc,char* argv[]){
    if (argv[1] == 0){
        printf("Usage: emu <rom_binary> \n");
        return -1;
    }
    bus mainbus = create_bus();
    make_rom(mainbus,512,0,argv[1]);
    make_ram(mainbus,512,512);
    make_core(mainbus);
    pthread_exit(NULL); 
}