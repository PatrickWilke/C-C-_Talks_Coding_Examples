
#ifndef MergeSortInC_h
#define MergeSortInC_h

#include "UtilitiesInC.h"

void MergeSortedCArrays(void* const src1,const int length1,void* const src2,const int length2 ,const int size,int (*ComparisonFunction)(void*,void*),void* const target);

void MergeSortC(void* const src,const int length, const int size,int (*ComparisonFunction)(void*,void*),void* const target);


#endif /* MergeSortInC_h */
