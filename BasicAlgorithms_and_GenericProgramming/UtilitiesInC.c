//  Created by Patrick Wilke on 13.12.18.

#include "UtilitiesInC.h"


//swap two arbitrary elements
void Swap(void* const target_1,void* const target_2,const int size_of_targets){
    
    //allocate temporary memory
    void* temp_memory=malloc(size_of_targets);
    
    //swap elements
    memcpy(temp_memory,target_1,size_of_targets);
    memcpy(target_1,target_2,size_of_targets);
    memcpy(target_2,temp_memory,size_of_targets);
    
    //free temporary memory
    free(temp_memory);
}


int LessThanInts(void* value_1, void* value_2){
    return (*((int*)value_1)<*((int*)value_2))? 1: 0;
}

int LessThanFloats(void* value_1, void* value_2){
    return (*((float*)value_1)<*((float*)value_2))? 1: 0;
}


