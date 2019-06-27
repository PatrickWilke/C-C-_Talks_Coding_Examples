//  Created by Patrick Wilke on 13.12.18.


#ifndef UtilitiesInC_h
#define UtilitiesInC_h

#include "string.h"
#include "stdlib.h"

#define SWAP(var1, var2) ({\
typeof(var1) tmp=var1;\
var1=var2;\
var2=tmp;\
})

void Swap(void* const target_1,void* const target_2,const int size_of_targets);

int LessThanInts(void* value_1, void* value_2);

int LessThanFloats(void* value_1, void* value_2);

#endif /* UtilitiesInC_h */
