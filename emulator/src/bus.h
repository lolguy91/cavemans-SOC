#ifndef __BUS_H__
#define __BUS_H__
typedef __UINT8_TYPE__(*bus_subscriber_t)(__UINT16_TYPE__ addr,__UINT8_TYPE__ val,int rw);
typedef struct {
    bus_subscriber_t subscribers[255];
    __UINT8_TYPE__ sub_count;
} bus_obj;

bus_obj buses[16];
__UINT8_TYPE__ bus_count = 0;

typedef struct {
    __UINT8_TYPE__ ID;
} bus;

void bus_write(bus bus,__UINT16_TYPE__ addr,__UINT8_TYPE__ val){
    if(bus.ID > bus_count){
        printf("rom balls\n");
        return;
    }

    for (__UINT8_TYPE__ i = 0; i < buses[bus.ID].sub_count; i++)
    {
        buses[bus.ID].subscribers[i](addr,val,1);
    }
} 
__UINT8_TYPE__ bus_read(bus bus,__UINT16_TYPE__ addr){
    if(bus.ID > bus_count){
        printf("bus balls %i,%i\n",bus_count,bus.ID);
        return 0;
    }

    for (__UINT8_TYPE__ i = 0; i < buses[bus.ID].sub_count; i++)
    {
        __UINT8_TYPE__ tmp = buses[bus.ID].subscribers[i](addr,0,0);
        if (tmp != 0) return tmp;
    }
    return 0;
} 
void bus_subscribe(bus b,bus_subscriber_t s){
    if(b.ID > bus_count){
        printf("bus balls\n");
        return;
    }
    buses[b.ID].subscribers[buses[b.ID].sub_count] = s; 
    buses[b.ID].sub_count++;
}
bus create_bus(){
    buses[bus_count].sub_count = 0;
    bus_count++;
    return (bus){bus_count- 1};

}


#endif // __BUS_H__