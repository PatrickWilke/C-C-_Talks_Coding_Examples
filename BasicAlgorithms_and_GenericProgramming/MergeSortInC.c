#include "MergeSortInC.h"


void MergeSortedCArrays(void* const src1,const int length1,void* const src2,const int length2 ,const int size,int (*ComparisonFunction)(void*,void*),void* const target){
    char* src1_char_pointer=(char*)src1;
    char* src2_char_pointer=(char*)src2;
    char* target_char_pointer=(char*)target;
    int index_first_array=0;
    int index_second_array=0;
    while (index_first_array<length1&&index_second_array<length2) {
        if (ComparisonFunction(src1_char_pointer+index_first_array*size,src2_char_pointer+index_second_array*size)) {
            memcpy(target_char_pointer+(index_first_array+index_second_array)*size,src1_char_pointer+index_first_array*size,size);
            index_first_array++;
        }
        else{
            memcpy(target_char_pointer+(index_first_array+index_second_array)*size,src2_char_pointer+index_second_array*size,size);
            index_second_array++;
        }
    }
    while (index_first_array<length1) {
        memcpy(target_char_pointer+(index_first_array+index_second_array)*size,src1_char_pointer+index_first_array*size,size);
        index_first_array++;
    }
    while (index_second_array<length2) {
        memcpy(target_char_pointer+(index_first_array+index_second_array)*size,src2_char_pointer+index_second_array*size,size);
        index_second_array++;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeSortC(void* const src,const int length, const int size,int (*ComparisonFunction)(void*,void*),void* const target){
    if (length>1) {
        const int new_length=length/2;
        void* left_site_pointer=malloc(new_length*size);
        void* right_site_pointer=malloc((length-new_length)*size);
        
        MergeSortC(src,new_length,size,ComparisonFunction,left_site_pointer);
    MergeSortC((char*)src+new_length*size,length-new_length,size,ComparisonFunction,right_site_pointer);
        MergeSortedCArrays(left_site_pointer,new_length,right_site_pointer,length-new_length,size,ComparisonFunction,target);
        
        free(left_site_pointer);
        free(right_site_pointer);
    }
    else{
        memcpy(target,src,size);
    }
    
}

