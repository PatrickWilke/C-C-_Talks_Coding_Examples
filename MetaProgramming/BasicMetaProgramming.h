//  Created by Patrick Wilke on 24.07.17.
//

#ifndef BasicMetaProgramming_h
#define BasicMetaProgramming_h

#include <iostream>

namespace MetaProg{
    
////////////////////////////////////////////////////////////////////////////////////////
    template <typename T,T i>
    struct ValueToType {
        const static T value= i;
        typedef T parametertype;
    };
    
////////////////////////////////////////////////////////////////////////////////////////
    template <bool statement, typename T1, typename T2>
    struct Switch {
        typedef T1 type;
    };
    
    template <typename T1, typename T2>
    struct Switch<false,T1,T2> {
        typedef T2 type;
    };
////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1, typename T2>
    struct Equal{
        typedef T2 type;
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    struct Max {
        template <typename T1, typename T2>
        struct apply{
            typedef typename Switch<(T2::value<T1::value), T1, T2>::type type;
        };
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    struct Min {
        template <typename T1, typename T2>
        struct apply{
            typedef typename Switch<(T2::value<T1::value), T2, T1>::type type;
        };
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    struct Add{
        template<typename T1,typename T2>
        struct apply{
            typedef ValueToType<typename T1::parametertype,(T1::value)+(T2::value)> type;
        };
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    struct Subtract{
        template<typename T1,typename T2>
        struct apply{
            typedef ValueToType<typename T1::parametertype,(T1::value)-(T2::value)> type;
        };
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    struct Increment{
        template<typename T1>
        struct apply{
            typedef ValueToType<typename T1::parametertype,(T1::value)+static_cast<typename T1::parametertype>(1) > type;
        };
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    struct Decrement{
        template<typename T1>
        struct apply{
            typedef ValueToType<typename T1::parametertype,(T1::value)-static_cast<typename T1::parametertype>(1) > type;
        };
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    struct Multiply{
        template<typename T1,typename T2>
        struct apply{
            typedef ValueToType<typename T1::parametertype,(T1::value)*(T2::value)> type;
        };
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    struct Square{
        template<typename T>
        struct apply{
            typedef ValueToType<typename T::parametertype,(T::value)*(T::value)> type;
        };
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    void PrintType(){
        std::cout<<T::value<<"\n";
    }
 ////////////////////////////////////////////////////////////////////////////////////////
    template<int i,typename func,typename data, typename ...additional_parameters>
    struct Iterate;
    
    template<int i,typename func,typename data,typename ...additional_parameters>
    struct Iterate{
        typedef typename func::template apply<typename Iterate<i-1,func,data,additional_parameters...>::type,additional_parameters...>::type type;
    };
    
    template<typename func,typename data,typename ...additional_parameters>
    struct Iterate<1,func,data,additional_parameters...>{
        typedef typename func::template apply<data,additional_parameters...>::type  type;
    };
    
    template<typename func,typename data,typename ...additional_parameters>
    struct Iterate<0,func,data,additional_parameters...>{
        typedef data  type;
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    struct Power{
        template<typename data,typename power>
        struct apply{
            typedef typename Iterate<power::value-1,Multiply,data,data>::type type;
        };
        template<typename data, typename Chosen_Int>
        struct apply<data, ValueToType<Chosen_Int,0>> {
            typedef ValueToType<Chosen_Int,1> type;
        };
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    template<int from, int to>
    struct Range;
    
    template<int to>
    struct Range<to,to>{
        typedef ValueToType<int,to> head;
        typedef void tail;
    };
    
    template<int from, int to>
    struct Range{
        typedef ValueToType<int,from> head;
        typedef typename Switch<(from<to),Range<from+1,to>,Range<from-1,to>>::type tail;
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    template<typename head_given,typename ...tail_given>
    struct CreateList;
    
    template<typename head_given,typename ...tail_given>
    struct CreateList{
        typedef head_given head;
        typedef CreateList<tail_given...> tail;
    };
    
    template<typename head_given>
    struct CreateList<head_given>{
        typedef head_given head;
        typedef void tail;
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    template<int integer_head,int ...integer_tail>
    struct CreateIntList;
    
    template<int head_given,int ...tail_given>
    struct CreateIntList{
        typedef ValueToType<int, head_given> head;
        typedef CreateIntList<tail_given...> tail;
    };
    
    template<int head_given>
    struct CreateIntList<head_given>{
        typedef ValueToType<int, head_given> head;
        typedef void tail;
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    void PrintList() {
        std::cout<<T::head::value<<"\n";
        PrintList<typename T::tail>();
    }
    
    template <>
    void PrintList<void>() {
    }
////////////////////////////////////////////////////////////////////////////////////////
    template <typename func, typename listhead, typename listtail>
    struct HelperApplyFunctionToList {
        typedef typename func::template apply<listhead>::type head;
        typedef HelperApplyFunctionToList<func,typename listtail::head,typename listtail::tail> tail;
    };
    
    template <typename func, typename listhead>
    struct HelperApplyFunctionToList<func,listhead,void> {
        typedef typename func::template apply<listhead>::type head;
        typedef void tail;
    };
    
    template <typename func, typename list>
    struct ApplyFunctionToList {
        typedef typename HelperApplyFunctionToList<func,typename list::head,typename list::tail>::head head;
        typedef typename HelperApplyFunctionToList<func,typename list::head,typename list::tail>::tail tail;
    };
 ////////////////////////////////////////////////////////////////////////////////////////
    template<typename list>
    struct ApplyFunctorToList {
        template<template<int> class TFunctor, class ...params>
        static void exec(params ...parameters){
            TFunctor<list::head::value>()(parameters...);
            ApplyFunctorToList<typename list::tail>::template exec<TFunctor>(parameters...);
        }
        
    };
    
    template<>
    struct ApplyFunctorToList<void> {
        template<template<int> class TFunctor, class ...params>
        static void exec(params ...parameters){
        }
    };
    
    
}//MetaProg


//template <int Number>
//class Functor {
//    
//public:
//    void operator ()(double d1, double d2){
//        std::cout<<d1*d2*static_cast<double>(Number)<<"\n";
//    }
//};
//MetaProg::ApplyFunctorToList<MetaProg::CreateIntList<8,27,39,42>>::exec<Functor>(1.5,2.5);

#endif /* BasicMetaProgramming_h */
