/************************************************
 *              CSCI 3410, HW 0
 *             Ring Buffers & FIR
 *************************************************/

#include <stdlib.h>
#include "ring.h"
int length =0;

struct ring * ring_create(int size) {

        if(size == 0){
                return NULL;
        }

        //first, make a ring pointer, and give it memory
        struct ring * ringPtr = (struct ring *) malloc (sizeof(struct ring));

        //make the capacity = size parameter
        ringPtr -> size = size;

        //give memory to ringPtr array
        ringPtr -> data = (short*) malloc (sizeof(short) * size);

        //make ringPtr read / write both 0 index
        ringPtr -> read = 0;
        ringPtr -> write = 0;


        return ringPtr;
}

int ring_size(struct ring *ring) {

        //if ring doesn't exist
        if(ring == NULL){
             return -1;   
        }


       
        //if there are no elements in ring
        if(ring -> read == ring -> write){
                return 0;
        }

        //else return the difference of read and write mod size
        return length;/*(ring-> write - ring->read) % ring-> size;*/
}



int ring_enqueue(struct ring *ring, short data) {
      
         //first, check if ring is null, or if the ring is full
        if(ring == NULL || ring_size(ring) == ring -> size){
                return -1;
        }


        ring->data[ring->write] = data;

        if(ring->write == ring-> size){
                ring->write = 0;
                length ++;
        }
        else{
                ring->write = ring->write+1 % ring->size;
                length ++;
        }
        

        return 0;
}



int ring_dequeue(struct ring *ring, short *datap) {
        
        //first, check if ring is null, or if the ring is empty
        
        if(ring == NULL || ring -> read == ring -> write){
                
                return -1;
        }

        short temp = 0;
        temp = ring->data[ring->read];
        ring->read = (ring->read + 1) % ring -> size;

        *datap = temp;
        if(length == 2){
                length = 1;
        }
        else{
                length--;
        }
        return 0;
}



double ring_apply_fir(struct ring *ring, double *weights) {
        
        //if ring is NULL or not full
        if(ring == NULL || ring_size(ring) != ring-> size){
                
                return 0;
        }

        int i = 0;
        int sum = 0;

        //loop through both arrays, multiple the elements at the same indexes, and add them together
   
        for(i=0; i< ring->size; i++){
                
                sum +=  weights[i] * ring->data[ring-> read + i];

        }

        return sum;
}

void ring_free(struct ring *ring) {
        free(ring);
}
