//  Created by Patrick Wilke on 13.12.18.

#ifndef Sorting_h
#define Sorting_h

#include <utility>
#include "Utilities.h"
#include "BubbleSort.h"
#include "HeapSort.h"
#include "QuickSort.h"


namespace PW {
    
    enum SortingAlgorithm {BUBBLESORT, QUICKSORT, HEAPSORT};
    
    //general sort function
    //arbitrary comparison function and algorithm type
    template< typename Iterator, typename CMP=std::less<>>
    bool Sort(Iterator start, Iterator end, CMP comparison_function={},     SortingAlgorithm alg=QUICKSORT){
        //    execute chosen algorithm
        switch (alg) {
            case QUICKSORT:
                QuickSort(start, end,comparison_function);
                return true;
            case HEAPSORT:
                HeapSort(start, end,comparison_function);
                return true;
            case BUBBLESORT:
                BubbleSort(start, end,comparison_function);
                return true;
            default:
                //            sorting failed
                std::cout <<"Error! Algorithm type not Supported.\n";
                return false;
        }
    
    }
    
    //sort with less relation and arb. algorithm
    template< typename Iterator>
    bool Sort(Iterator start, Iterator end,SortingAlgorithm alg){
        Sort(start, end,std::less<>(),alg);
        return true;
    }
    
    //quicksort with no relation given but pivot-function
    template <typename Iterator, typename CMP,typename pvtfct>
    bool Sort(Iterator start, Iterator end,SortingAlgorithm QUICKSORT,pvtfct    pivot_function){
        QuickSort(start, end,std::less<>(),pivot_function);
        return true;
    }
    
    //quicksort with given relation and pivot-function
    template< typename Iterator, typename CMP,typename pvtfct>
    bool Sort(Iterator start, Iterator end, CMP comparison_function,    SortingAlgorithm QUICKSORT,pvtfct pivot_function){
        QuickSort(start, end,comparison_function,pivot_function);
        return true;
    }
    
}

#endif /* Sorting_h */
