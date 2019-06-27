#include "BubbleSortInC.h"

void BubbleSortC(void* const start,const int number_of_elements,const int size,int (*comparison_function)(void*,void*)){
    
//    iterate all elements
  int iteration_index;
  for(iteration_index=0;iteration_index<number_of_elements;++iteration_index){//all elements
      
//      compare elements
      int current_element;
      for(current_element=0;current_element<number_of_elements-iteration_index-1;++current_element){//move to the right
          
          if((*comparison_function)((char*)start+(current_element+1)*size,(char*)start+current_element*size)){//property fulfilled
              
              Swap((char*)start+(current_element+1)*size,(char*)start+(current_element)*size,size);
              
          }//property fulfilled
      }//move to the right
  }//all elements
}//BubbleSortC
