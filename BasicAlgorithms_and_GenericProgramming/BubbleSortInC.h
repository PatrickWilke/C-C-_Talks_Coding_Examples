//  Created by Patrick Wilke on 13.12.18.

#ifndef BubbleSortInC_h
#define BubbleSortInC_h

#include "UtilitiesInC.h"


void BubbleSortC(void* const start,const int number_of_elements,const int size,int (*comparison_function)(void*,void*));

#endif /* BubbleSortInC_h */
