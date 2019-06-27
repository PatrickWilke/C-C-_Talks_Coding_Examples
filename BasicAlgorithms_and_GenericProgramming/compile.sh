#/bin/bash

gcc -c UtilitiesInC.c BubbleSortInC.c MergeSortInC.c
g++ -std=c++17 -o GenericSorting.out main.cpp Stopwatch.cpp UtilitiesInC.o BubbleSortInC.o MergeSortInC.o -O2
