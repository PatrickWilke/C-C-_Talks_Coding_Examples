//  Created by Patrick Wilke on 13.12.18.

#ifndef BubbleSort_h
#define BubbleSort_h

#include "Utilities.h"
#include <utility>

namespace PW {
   
    template <typename Iterator, typename CMP=std::less<>>
    void BubbleSort(const Iterator  start,const Iterator end,CMP    comparison_function = {}){
    
        //    Check if array has more than 1 element
        if (std::next(start)==end||start==end) {
            return;
        }
        Iterator tmp_end=end;
        //    iterate all elements
        for(Iterator    iteration_position=start;std::next  (iteration_position)!=end;++iteration_position){//all elements
    
            //      compare elements
            Iterator current_element=start;
            for(;std::next(current_element)!=tmp_end;++current_element){//move to   the right
    
                    if(comparison_function(*std::next   (current_element),*current_element)){//property fulfilled
    
                    Swap(*std::next(current_element),*current_element);
    
                }//property fulfilled
            }//move to the right
            tmp_end=current_element;
        }// all elements
    }//void BubbleSort

}

#endif /* BubbleSort_h */
