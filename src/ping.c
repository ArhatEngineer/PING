#include "../include/ping.h"

/*
sptr = source pointer
dptr = destination pointer
*/


int8_t *evalicmp(icmp *pkt) {
    int8_t *p;
    int16_t size;

   ricmp rawpkt;

    //check if we have a packet 
    //check if the packet holds data
    if(!pkt || !pkt->data){
    //return an error
        return 0;
    }

    switch (pkt->kind) {
        case echo:
        //Control Message Type 8 – Echo Request |code field:0 | Echo request (used to ping) 
            rawpkt.type = 8;
            rawpkt.code = 0;
            break;
        case echoreply:
            //Control Message Type 0 – Echo Reply | code field:0 | Echo reply (used to ping) 
            rawpkt.type = 0;
            rawpkt.code = 0;
            break;
        
        default:
            return 0;
            break;
    }

    rawpkt.checksum = checksum(pkt);
    //size is the byte size of the entire rawicmp struct that contains the packet + the pkt size itself
    size = sizeof(struct s_rawicmp) + pkt->size;
    //dynamically allocating a some plot of memory that is the size of the struct and pkt size itself that 
    //we got above
    p = malloc(size);
    //asserting that malloc (memory allocation) worked correctly and there exists a location in memory 
    //that isthe correct size that we can use.
    assert(p);
    //zeros out all slots of the plot of memory so that there are no random extraneous values when rebuilding or
    //analyzing the incoming packet.
    zero(p, size);


    copy(p, &rawpkt, sizeof(struct s_rawicmp));

}



void copy(int8_t *dst, int8_t* src, int16_t size) {
    int16_t n;
    int8_t *sptr, *dptr;

    for (dptr = dst, sptr=src, n=size; n; n--) {
        // When the pluses come after it means it will evaluate *dptr = *sptr and then
        // do the increment operation. Meaning operation and then incrementation.
        *dptr++ =  *sptr++;
    return;
}
}


icmp *mkicmp(type kind, const int8_t *data, int16_t size){
    int16_t n;
    icmp *p;
    
    if(!data || !size) {
        return (icmp *)0;
    }
    n = sizeof(struct s_icmp) + size;
    p = (icmp *)malloc(n);
    assert(p);
    zero(p, n);


    //p->kind is really (*p).kind
    //Meaning you are not directly calling the kind variable of the original struct
    //BUT calling the variable through a pointer to the structure itself.
    p->kind = kind;
    //pointer of size is the payload of the packet
    p->size = size;
    p->data = data;


    return p;
}


void showicmp(icmp *pkt) {
    
    if(!pkt){return;}

    printf("kind: \t %s\nsize:\t %d\npayload:\n",
        (pkt->kind == echo) ? "echo" : "echo reply",
        pkt->size);
    if (pkt-> data)
        printhex(pkt->data, pkt->size,    0);
    printf("\n");

    return;

}


int main(int argc, char*argv[]) {
    return 0;
}


//OLD CODE BELOW
    //copying data (a pointer of an array of packet data) to the memory location at address which is tagged as the 
    //address of the pointer p (to the struct icmp) and variable data and the size is how much data is being copied
    //to that location
    // copy($1 &p->data, data, size)
    // p->checksum = checksum(p);


