//  Created by Patrick Wilke on 12.11.18.


#include <random>
#include <functional>
#include <vector>

#include "Stopwatch.h"
#include "Sorting.h"


extern "C"{
    
#include "BubbleSortInC.h"
#include "MergeSortInC.h"
    
}

int main(int argc, const char * argv[]) {

    Stopwatch watch;
    std::vector<int> test_case(1<<15);
    std::mt19937_64 engine;
    auto random_numbers=std::bind(std::uniform_int_distribution<int>(-(1<<13),1<<13), engine);
    
    for (auto& x : test_case) {
        x=random_numbers();
    }
    auto test_copy1(test_case);
    auto test_copy2(test_case);
    auto test_copy3(test_case);
    auto test_copy4(test_case);

    std::cout<<"C++ BubbleSort, HeapSort and QuickSort;\n";
    std::cout<<"C BubbleSort and MergeSort:\n";
    watch.Start();
    PW::Sort(test_case.begin(), test_case.end(),PW::BUBBLESORT);
    watch.StopAndRestart();
    PW::Sort(test_copy1.begin(), test_copy1.end(),PW::HEAPSORT);
    watch.StopAndRestart();
    PW::Sort(test_copy2.begin(), test_copy2.end(),PW::QUICKSORT);
    watch.StopAndRestart();
    BubbleSortC(test_copy3.data(),test_copy3.size(),sizeof(int),LessThanInts);
    watch.StopAndRestart();
    MergeSortC(test_copy4.data(),test_copy4.size(),sizeof(int),LessThanInts,test_copy4.data());
    watch.Stop();
    watch.PrintAll();
   
    
    return 0;
}
