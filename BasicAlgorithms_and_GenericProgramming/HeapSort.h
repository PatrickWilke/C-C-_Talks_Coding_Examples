//  Created by Patrick Wilke on 13.12.18.

#ifndef HeapSort_h
#define HeapSort_h

#include "Utilities.h"
#include <utility>

namespace PW {
    
    
    //Create a heap out of a c-array like structure and sort it
    template <typename Iterator, typename CMP>
    class Heap{
    
    public:
        //    Constructor
        Heap(const Iterator start,const Iterator end,CMP    comparison_function):start_{start}, size_{end-start},   comparison_function_{comparison_function}{}
    
        //    Make the array into a heap
        void MakeHeap(){
            for (long i=(size_>>1)-1; -1<i; --i) {
                Heapify(i);
            }
        }
    
        //    Sort an array by creating a heap
        void Sort(){
            MakeHeap();
            for (long i=size_-1; i; --i) {
                Swap(start_[i], start_[0]);
                --size_;
                Heapify(0);
            }
        }
    
        //  return start of the heap
        Iterator GetStart()const{
            return start_;
        }
    
        //  return size of the heap
        long GetSize()const{
            return size_;
        }
    
    private:
        //    helper function which makes sure the branch starten at element is a   proper heap. It assumes both child branches to be proper heaps
        void Heapify(const long element){
    
            long left=Left(element);
            long right=Right(element);
            long maximum = element;//maximum is missleading in the general case.    (element which fulfills comparison fumction)
    
            if (left < size_ &&     comparison_function_(start_[maximum],start_[left])) {
                maximum=left;
            }
            if (right< size_ &&     comparison_function_(start_[maximum],start_[right])) {
                maximum=right;
            }
            if (maximum!=element) {
                Swap(start_[element], start_[maximum]);
                Heapify(maximum);
            }
        }
        //    get parent node of an element
        long Parent(const long position)const{
            return position>>1;
        }
        //    get left child node of an element
        long Left(const long position)const{
            return position<<1;
        }
        //    get right child node of an element
        long Right(const long position)const{
            return (position<<1)+1;
        }
        //    private members
        Iterator start_;
        long  size_;
        CMP comparison_function_;
    };
    
    template< typename Iterator, typename CMP=std::less<>>
    void HeapSort(Iterator start, Iterator end, CMP comparison_function={}){
    
        //    Check if array has more than 1 element
        if (std::next(start)==end||start==end) {
            return;
        }
    
        //    sort container with random access
        if constexpr(std::is_same<std::random_access_iterator_tag,typename  std::iterator_traits<Iterator>::iterator_category>::value) {
            Heap heap(start,end,comparison_function);
            heap.Sort();
        }
        //    sort lists by creating a c-array first (linear in memory)
        else{
            std::vector<typename std::iterator_traits<Iterator>::value_type> tmp;
            for (Iterator element=start; element!=end;++element) {
                tmp.push_back(*element);
            }
            Heap heap(tmp.begin(),tmp.end(),comparison_function);
            heap.Sort();
            //        copy results back into the list
            for (long i=0; i<tmp.size(); ++i) {
                *start=tmp[i];
                ++start;
            }
        }
    }
    
}

#endif /* HeapSort_h */
