//  Created by Patrick Wilke on 13.12.18.

#ifndef QuickSort_h
#define QuickSort_h

#include "Utilities.h"
#include <utility>

namespace PW {
    
    //Function which is used in Quick Sort to choose a pivot element
    template <typename T>
    struct FirstElementAsPivot{
    public:
        FirstElementAsPivot(){};
        constexpr T operator()(const T& x,const T& y) {
            return x;
        }
    };
 
    //partition the container given by start and end based on a chosen pivot and comparison function
    //used in quick sort
    template <typename Iterator ,typename CMP>
    Iterator partition(const Iterator start,const Iterator end, Iterator pivot, CMP comparison_function){
        auto pivot_value=*pivot;
        Iterator left=start;
        
        //    make sure all elements fulfilling comparison_function are on the left of left
        for (Iterator right=start; right!=end; ++right) {
            if (comparison_function(*right,pivot_value)) {
                Swap(*right, *left);
                ++left;
            }
        }
        //    put the pivot at position left
        if (pivot_value==*pivot) {
            Swap(*left, *pivot);
        }
        else{
            Iterator tmp=left;
            for (; *tmp!=pivot_value; ++tmp) {}
            Swap(*left, *tmp);
        }
        //    return pivot position
        return left;
    }
    
    template <typename Iterator, typename CMP=std::less<>, typename     pvtfct=FirstElementAsPivot<Iterator>>
    void QuickSort(const Iterator  start,const Iterator end,CMP     comparison_function = {}, pvtfct pivot_func={}){
    
        //    Check if array has more than 1 element
        if (start==end||std::next(start)==end) {
            return;
        }
        //    partition the array and get position of the pivot
        Iterator pivot_position=partition(start, end, pivot_func(start,end),    comparison_function);
        //    sort the two new arrays
        QuickSort(start, pivot_position,comparison_function,pivot_func);
        QuickSort(std::next(pivot_position),end,comparison_function,pivot_func);
    }

}

#endif /* QuickSort_h */
